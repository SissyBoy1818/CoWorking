from database import *

from fastapi import FastAPI, HTTPException, Depends
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from pydantic import BaseModel
from passlib.context import CryptContext
import jwt
from datetime import datetime, timedelta


# Инициализируем сервер и базу данных
app = FastAPI()
db = DataBase()

# Задаем параметры кодировки JSW и время жизни токена
SECRET_KEY = "key123321"
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 60

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")

# Структуры токена и запроса на аунтификацию
class AuthRequest(BaseModel):
    login: str
    password: str

class Token(BaseModel):
    access_token: str
    token_type: str

# Получение айди пользователя по JSW токену
def get_user_id(token: str = Depends(oauth2_scheme)):
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        user_id = payload.get("sub")
        if user_id is None:
            raise HTTPException(status_code=401, detail="Неверный токен1")
        return user_id
    except jwt.ExpiredSignatureError:
        raise HTTPException(status_code=401, detail="Токен просрочен")
    except Exception as e:
        raise HTTPException(status_code=401, detail=repr(e))

# Создание токена с заданным временем жизни
def create_access_token(data: dict, expires_delta: timedelta | None = None):
    to_encode = data.copy()
    if expires_delta:
        expire = datetime.utcnow() + expires_delta
    else:
        expire = datetime.utcnow() + timedelta(minutes=15)
    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)
    return encoded_jwt

# POST запрос на авторизацию пользователя
@app.post("/token")
def login(form_data: OAuth2PasswordRequestForm = Depends()):
    account_id = db.sign_in(form_data.username, form_data.password)
    if account_id is None:
        raise HTTPException(status_code=401, detail="Invalid login/password")

    access_token_expires = timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    access_token = create_access_token(
        data={"sub": str(account_id)}, expires_delta=access_token_expires
    )

    return {"access_token": access_token, "token_type": "bearer"}

# POST запрос на бронирование рабочего места
@app.post("/book_workplace")
def book_workplace(workplace_id: int, timestamp_str: str, hours: int,
                   token: str = Depends(oauth2_scheme)):
    user_id = get_user_id(token)

    try:
        timestamp = datetime.strptime(timestamp_str, "%Y-%m-%d %H:%M:%S")
        duration = timedelta(hours=hours)
        if db.book_workplace(user_id, workplace_id, timestamp, duration):
            return {"Success": True}
        else:
            raise HTTPException(status_code=500, detail="Invalid arguments")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# POST запрос на бронирование комнаты для совещаний
@app.post("/book_room")
def book_room(room_id: int, timestamp_str: str, hours: int, event: str,
                   token: str = Depends(oauth2_scheme)):
    user_id = get_user_id(token)

    try:
        timestamp = datetime.strptime(timestamp_str, "%Y-%m-%d %H:%M:%S")
        duration = timedelta(hours=hours)
        if db.book_room(user_id, room_id, timestamp, duration):
            return {"Success": True}
        else:
            raise HTTPException(status_code=500, detail="Invalid arguments")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# GET запрос на получение всех рабочих мест
@app.get("/workplaces")
def get_workplaces(token: str = Depends(oauth2_scheme)):
    return db.get_workplaces()

# GET запрос на получение всех комнат
@app.get("/rooms")
def get_rooms(token: str = Depends(oauth2_scheme)):
    return db.get_rooms()

# TODO:
# - Получение всех броней
# - Регистрация пользователей
# - Отмена бронирования
# - Добавление/удаление рабочих мест и комнат