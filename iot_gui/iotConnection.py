import time as t
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

if __name__ == "__main__":
        def customCallback(client, userdata, message):
                topic = message.topic
                payload = message.payload.decode("utf-8")
                print('Topic: '+topic+str(type(payload))+' Payload: '+str(payload))
        myAWSIoTMQTTClient.subscribe("aws/test",1,customCallback)       
        while True:
                t.sleep(2)

