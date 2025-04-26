import requests
import time
import json

BACKEND_URL = 'http://localhost:8000'

def make_user(username, password):
    return {
        'username': username,
        'password': password
    }

def make_project(name, description):
    return {
        'name': name,
        'description': description
    }

registered_user = make_user('landiluigi746', 'simplePW1*')
unregistered_user = make_user('whotfami12', 'mystupidAsspw*2')

projects = [
    make_project('Lavoro TPS', 'Lavoro di gruppo di TPS su Thread e Semafori in C'),
    make_project('BigCaos', 'The first 10th gen videogame, an open-world fps-rpg made with Unreal Engine 6!!! KEEP VERY SECRET!!!'),
    make_project('Invalid desc', 'a' * 1024), # description too large
    make_project('Invalid desc2', ''),
]

def do_login(user):
    s = requests.Session()
    res = s.post(BACKEND_URL + '/users/login', json=user)

    if res.headers.get("Authorization"):
        s.headers["Authorization"] = res.headers["Authorization"]

    return s

def reg_test(user):
    s = do_login(user)
    
    for project in projects:
        res = s.post(BACKEND_URL + '/projects/register', json=project)

        if not res.ok:
            print(f"Project Registration failed | Status code: {res.status_code}, Error message: {res.text}")
        else:
            print(f"Project Registration successful")

def get_test(user):
    s = do_login(user)

    res = s.post(BACKEND_URL + '/projects/get')

    if not res.ok:
        print(f"Failed to fetch projects")
    else:
        print(f"Projects: {res.json()}")


# reg_test(registered_user)
# time.sleep(4)
# reg_test(unregistered_user)
# time.sleep(4)
get_test(registered_user)
time.sleep(4)
get_test(unregistered_user)
