from datetime import datetime, timedelta
import sqlite3
import json
from passlib.context import CryptContext

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")


class DataBase:
    def __init__(self, db_path: str = "CoWorking server/coworking.db"):
        self.db_path = db_path

    def sign_in(self, login: str, password: str):
        connection = sqlite3.connect(self.db_path)
        cursor = connection.cursor()

        query: str = "SELECT id, password_hash FROM users WHERE email = ?"
        cursor.execute(query, (login,))

        result = cursor.fetchone()
        if result is None:
            return None

        user_id, password_hash = result
        if password_hash == password:
            return user_id
        return None

    def book_workplace(self, user_id: int, workplace_id: int,
                       timestamp: datetime, duration: timedelta):
        connection = sqlite3.connect(self.db_path)
        cursor = connection.cursor()

        # Проверка
        query: str = "SELECT timestamp, duration FROM workplace_bookings WHERE workplace_id = ?"
        cursor.execute(query, (workplace_id,))

        result = cursor.fetchall()
        for reserved_timestamp, reserved_duration in result:
            reserved_timestamp = datetime.strptime(reserved_timestamp, "%Y-%m-%d %H:%M:%S")
            reserved_duration = timedelta(hours=reserved_duration)
            if (reserved_timestamp < timestamp < reserved_timestamp + reserved_duration) and \
                (reserved_timestamp < timestamp + duration < reserved_timestamp + reserved_duration):
                return False

        # Вставка
        query: str = "INSERT INTO workplace_bookings (user_id, workplace_id, timestamp, duration) VALUES (?, ?, ?, ?)"
        cursor.execute(query, (user_id, workplace_id, timestamp.strftime("%Y-%m-%d %H:%M:%S"), duration.seconds//3600))

        connection.commit()
        return True

    def book_room(self, user_id: int, room_id: int,
                       timestamp: datetime, duration: timedelta, event: str):
        connection = sqlite3.connect(self.db_path)
        cursor = connection.cursor()

        # Проверка
        query: str = "SELECT timestamp, duration FROM room_bookings WHERE room_id = ?"
        cursor.execute(query, (room_id,))

        result = cursor.fetchall()
        for reserved_timestamp, reserved_duration in result:
            if (reserved_timestamp < timestamp < reserved_timestamp + reserved_duration) and \
                (reserved_timestamp < timestamp + duration < reserved_timestamp + reserved_duration):
                return False

        # Вставка
        query: str = "INSERT INTO room_bookings (user_id, room_id, timestamp, duration, event) VALUES (?, ?, ?, ?, ?)"
        cursor.execute(query, (user_id, room_id, timestamp.strftime("%Y-%m-%d %H:%M:%S"), duration.seconds//3600, event))

        connection.commit()
        return True

    def get_workplaces(self):
        connection = sqlite3.connect(self.db_path)
        connection.row_factory = sqlite3.Row
        cursor = connection.cursor()

        query: str = "SELECT * FROM workplaces"
        cursor.execute(query)

        rows = cursor.fetchall()
        result = [dict(row) for row in rows]

        json_result = json.dumps(result, ensure_ascii=False)

        return json_result

    def get_rooms(self):
        connection = sqlite3.connect(self.db_path)
        connection.row_factory = sqlite3.Row
        cursor = connection.cursor()

        query: str = "SELECT * FROM rooms"
        cursor.execute(query)

        rows = cursor.fetchall()
        result = [dict(row) for row in rows]

        json_result = json.dumps(result, ensure_ascii=False)

        return json_result