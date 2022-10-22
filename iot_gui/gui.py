# from iotConnection import myAWSIoTMQTTClient
from tkinter import *
import json
import AWSIoTPythonSDK.MQTTLib as AWSIoTPyMQTT

# Define ENDPOINT, CLIENT_ID, PATH_TO_CERTIFICATE, PATH_TO_PRIVATE_KEY, PATH_TO_AMAZON_ROOT_CA_1, MESSAGE, TOPIC, and RANGE
ENDPOINT = "a1cge2lifgjxnq-ats.iot.us-east-1.amazonaws.com"
CLIENT_ID = "gui_control_client"
PATH_TO_CERTIFICATE = "secrets/5c6e7c05efeb408401bc839026f41b9bfcda20af214ec8251472715b3f3ba6c2-certificate.pem.crt"
PATH_TO_PRIVATE_KEY = "secrets/5c6e7c05efeb408401bc839026f41b9bfcda20af214ec8251472715b3f3ba6c2-private.pem.key"
PATH_TO_AMAZON_ROOT_CA_1 = "secrets/AmazonRootCA1.pem"
RANGE = 20

myAWSIoTMQTTClient = AWSIoTPyMQTT.AWSIoTMQTTClient(CLIENT_ID)
myAWSIoTMQTTClient.configureEndpoint(ENDPOINT, 8883)
myAWSIoTMQTTClient.configureCredentials(PATH_TO_AMAZON_ROOT_CA_1, PATH_TO_PRIVATE_KEY, PATH_TO_CERTIFICATE)

myAWSIoTMQTTClient.connect()
temperature = None
humidity = None
soil_moisture = None
auto_on = True
sprinkler_on = True
sprinkler_state = None
# def publish():
#     myAWSIoTMQTTClient.configureAutoReconnectBackoffTime(1, 32, 20)
#     myAWSIoTMQTTClient.configureOfflinePublishQueueing(-1)
#     myAWSIoTMQTTClient.configureDrainingFrequency(2)
#     myAWSIoTMQTTClient.configureConnectDisconnectTimeout(10)
#     myAWSIoTMQTTClient.configureMQTTOperationTimeout(5)
def switch(change = True):
    global auto_on
     
    # Determine is on or off
    if auto_on:
        auto_button.config(image = off)
        
        auto_on = False
    else:
       
        auto_button.config(image = on)
        auto_on = True
    if change:
        command(change=True)
def switch1(change = True):
    global sprinkler_on
     
    # Determine is on or off
    if sprinkler_on:
        sprinkler_button.config(image = off)
        
        sprinkler_on = False
    else:
       
        sprinkler_button.config(image = on)
        sprinkler_on = True
    if change:
        command(change=True)
def refresh(client, userdata, message):
    global humidity,temperature,soil_moisture,auto_on,sprinkler_on
    payload = message.payload.decode("utf-8")
    payload = json.loads(payload)
    humidity = payload['humidity']
    temperature = payload['temperature']
    soil_moisture = payload['soil_moisture']
    auto_on = not(bool(payload['auto']))
    sprinkler_on = not(bool(payload["on_state"]))
    sprinkler_state = bool(payload["state"])
    switch(change = False)
    switch1(change = False)
    moisture_label.config(text=f"Soil Moisture : {soil_moisture}")
    temperature_label.config(text=f"Temperature : {temperature}")
    humidity_label.config(text=f"Humidity : {humidity}")
    sprinkler_label.config(text="Sprinkler State : {}".format("ON" if sprinkler_state else "OFF"))
myAWSIoTMQTTClient.subscribe("gui/refresh",1,refresh)
def command(change = False):
    doc = dict()
    if change:
        # doc = dict()
        doc['action'] = 1
        # doc['humidity'] = humidity
        # doc['temperature'] = temperature
        # doc["soil_moisture"] = soil_moisture
        doc["auto"] = int(auto_on)
        doc["on_state"] = int(sprinkler_on)
    else :
        doc["action"] = 0
    docJson = json.dumps(doc)
    myAWSIoTMQTTClient.publish("esp8266/control",docJson,1)

root = Tk()
root.title("CONTROLLER")
root.geometry('400x500')
refresh_button = Button(root,text="REFRESH",background="blue",font=('TimesNewRoman',12),foreground='white',height=1,width=10,command=command)
refresh_button.place(x=150,y=10)
moisture_label = Label(root,text=f"Soil Moisture : {soil_moisture}",background="lightgrey",font=('TimesNewRoman',12))
moisture_label.place(x=25,y=50,height=50,width=350)
temperature_label = Label(root,text=f"Temperature : {temperature}",background="lightgrey",font=('TimesNewRoman',12))
temperature_label.place(x=25,y=125,height=50,width=350)
humidity_label = Label(root,text=f"Humidity : {humidity}",background="lightgrey",font=('TimesNewRoman',12))
humidity_label.place(x=25,y=200,height=50,width=350)
sprinkler_label = Label(root,text="Sprinkler State : {}".format("ON" if sprinkler_state else "OFF"),background="lightgrey",font=('TimesNewRoman',12))
sprinkler_label.place(x=25,y=275,height=50,width=350)
on = PhotoImage(file = "state1.png",height=50)
off = PhotoImage(file = "state2.png",height=50)
auto_button = Button(root, image = on, bd = 0,command = switch)
auto_button.place(x = 150,y=350)
sprinkler_button = Button(root, image = on, bd = 0,command = switch1)
sprinkler_button.place(x = 150,y=425)
auto_label =  Label(root,text="Auto",font=('TimesNewRoman',16))
auto_label.place(x=50,y=350,height=50,width=100)
default_label =  Label(root,text="Manual",font=('TimesNewRoman',16))
default_label.place(x=250,y=350,height=50,width=100)
on_label =  Label(root,text="ON",font=('TimesNewRoman',16))
on_label.place(x=50,y=430,height=50,width=100)
of_label =  Label(root,text="OFF",font=('TimesNewRoman',16))
of_label.place(x=250,y=430,height=50,width=100)
root.mainloop()