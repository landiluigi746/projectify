import requests
import time

BACKEND_URL = 'http://localhost:8000'

def make_user(username, password):
    return {
        'username': username,
        'password': password
    }

def make_link(name, url, projectID):
    return {
        'projectID': projectID,
        'name': name,
        'url': url
    }

registered_user = make_user('landiluigi746', 'simplePW1*')
unregistered_user = make_user('whotfami12', 'mystupidAsspw*2')

projectIDs = [1, 2, 99, 999]

links = [
    make_link("googlez", "https://www.google.com", 1),
    make_link("github", "https://github.com", 2),
    make_link("amazononzio", "https://www.amazon.com/", 2),
    make_link("This should not be here (invalid project ID)", "https://www.google.com", 99),
    make_link("This should not be here (invalid URL)", "bruh this is invalid", 2)
]

def do_login(user):
    s = requests.Session()
    res = s.post(BACKEND_URL + '/users/login', json=user)

    if res.headers.get("Authorization"):
        s.headers["Authorization"] = res.headers["Authorization"]

    return s

def reg_test(user):
    s = do_login(user)

    for link in links:
        res = s.post(BACKEND_URL + '/links/register', json=link)

        if not res.ok:
            print(f"Link Registration failed | Status code: {res.status_code}, Error message: {res.text}")
        else:
            print(f"Link Registration successful")

def get_test(user):
    s = do_login(user)

    for projectID in projectIDs:
        res = s.post(BACKEND_URL + '/links/get', json={'projectID':projectID})

        if not res.ok:
            print(f"Failed to fetch links for project ID {projectID}")
        else:
            print(f"Links: {res.json()}")

reg_test(registered_user)
time.sleep(4)
reg_test(unregistered_user)
time.sleep(4)
get_test(registered_user)
time.sleep(4)
get_test(unregistered_user)
