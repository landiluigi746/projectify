import requests
import time

BACKEND_URL = 'http://localhost:8000'

def make_user(username, password):
    return {
        'username': username,
        'password': password
    }

users = [
    make_user('landiluigi746', 'simplePW1*'),
    make_user('1brrbrrpatapim', 'slim1234'),
    make_user('ValidUsername', 'InvalidPW'),
    make_user('Siummaldo', 'yEBroItWorks25*')
]

reg_status = [0] * len(users)
login_status = [0] * len(users)

def reg_test():
    for i, user in enumerate(users):
        res = requests.post(BACKEND_URL + '/register', json=user)

        reg_status[i] = res.status_code

        if not res.ok:
            print(f"Registration failed | Status code: {res.status_code}, Error message: {res.text}")
        else:
            print(f"Registration successful")

def login_test():
    for i, user in enumerate(users):
        res = requests.post(BACKEND_URL + '/login', json=user)

        login_status[i] = res.status_code

        if not res.ok:
            print(f"Login failed | Status code: {res.status_code}, Error message: {res.text}")
        else:
            print(f"Login successful | Backend returned: {res.text}")

reg_test()
time.sleep(4)
login_test()
