import pyrebase

config = {
    'apiKey': "AIzaSyCMjeQs6i4x84u59GPLsRVJJWCFEi-dwrE",
    'authDomain': "test-f6da5.firebaseapp.com",
    'projectId': "test-f6da5",
    'databaseURL': 'https://test-f6da5-default-rtdb.asia-southeast1.firebasedatabase.app/',
    'storageBucket': "test-f6da5.appspot.com",
    'messagingSenderId': "1021371619089",
    'appId': "1:1021371619089:web:f4779047c8a95e1417deb0"
}

firebase = pyrebase.initialize_app(config)
database = firebase.database()

data={
    "Temp": 37,
    "Humid": 28
}

database.update(data)