import requests
import time

BACKEND_URL = 'http://localhost:8000'

def make_user(username, password):
    return {
        'username': username,
        'password': password
    }

def make_task(name, projectID):
    return {
        'projectID': projectID,
        'name': name
    }

registered_user = make_user('landiluigi746', 'simplePW1*')
unregistered_user = make_user('whotfami12', 'mystupidAsspw*2')

projectIDs = [1, 2, 99, 999]

toggle_payloads = []

tasks = [
    make_task("Finire la cacchios di presentaziones", 1),
    make_task("Implementare l'IA di Brr Brr Patapim", 2),
    make_task("Fixare il livello di doodle jump", 2),
    make_task("This should not be here", 99),
    make_task("This should not be here", 999)
]

fetched_tasks = {}

def do_login(user):
    s = requests.Session()
    res = s.post(BACKEND_URL + '/users/login', json=user)

    if res.headers.get("Authorization"):
        s.headers["Authorization"] = res.headers["Authorization"]

    return s

def reg_test(user):
    s = do_login(user)

    for task in tasks:
        res = s.post(BACKEND_URL + '/tasks/register', json=task)

        if not res.ok:
            print(f"Task Registration failed | Status code: {res.status_code}, Error message: {res.text}")
        else:
            print(f"Task Registration successful")

def get_test(user):
    s = do_login(user)

    for projectID in projectIDs:
        res = s.post(BACKEND_URL + '/tasks/get', json={'projectID':projectID})

        if not res.ok:
            print(f"Failed to fetch tasks for project ID {projectID}")
        else:
            json = res.json()
            fetched_tasks[user["username"]] = json

            for item in json:
                payload = {
                    'taskID': item["ID"],
                    'projectID': projectID
                }

                toggle_payloads.append(payload)

            print(f"Tasks: {res.json()}")

def toggle_test(user):
    s = do_login(user)

    for payload in toggle_payloads:
        res = s.post(BACKEND_URL + '/tasks/toggleStatus', json=payload)

        if not res.ok:
            print(f"Task toggle status failed | Status code: {res.status_code}, Error message: {res.text}")
        else:
            print(f"Task toggle status successful")

def del_test(user):
    if not fetched_tasks[user["username"]]:
        pass

    s = do_login(user)

    for task in fetched_tasks[user["username"]]:
        res = s.post(BACKEND_URL + '/tasks/delete', json={
            'taskID': task["ID"],
            'projectID': task["projectID"]
        })

        if not res.ok:
            print(f"Task deletion failed")
        else:
            print(f"Task deleted successfully")


# reg_test(registered_user)
# # time.sleep(4)
# # reg_test(unregistered_user)
# time.sleep(4)
get_test(registered_user)
# time.sleep(4)
# get_test(unregistered_user)
# time.sleep(4)
# toggle_test(registered_user)
del_test(registered_user)
time.sleep(4)
get_test(registered_user)
