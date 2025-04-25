import requests
import time

BACKEND_URL = 'http://localhost:8000'

def make_user(username, password):
    return {
        'username': username,
        'password': password
    }

registered_user = make_user('landiluigi746', 'simplePW1*')
unregistered_user = make_user('whotfami12', 'mystupidAsspw*2')

def test(user):
    s = requests.Session()
    res = s.post(BACKEND_URL + '/login', json=user)

    if res.headers.get("Authorization"):
        s.headers["Authorization"] = res.headers["Authorization"]

    prot_res = s.get(BACKEND_URL + '/protected')

    if s.headers.get("Authorization"):
        assert prot_res.status_code == 200
    else:
        assert prot_res.status_code == 401

    print(f"Backend says: {prot_res.text}")

test(registered_user)
time.sleep(4)
test(unregistered_user)
