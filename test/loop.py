import requests
import time

endpoint = "http://192.168.43.222/ajax"
channel_count = int(requests.get(endpoint + "/pwm/channelCount", timeout=5).text)
print(channel_count)
test_data = [0] * channel_count
while True:
    for i in range(0, len(test_data)):
        test_data[i] = 10;
        response = requests.post(endpoint + "/pwm/asArray", json=test_data, timeout=5)
        print(test_data)
        test_data[i] = 0;
        time.sleep(0.3)
