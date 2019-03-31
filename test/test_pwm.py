import unittest
import requests
import json


class TestPwmApi(unittest.TestCase):
    def setUp(self):
#        self.endpoint = "http://192.168.0.160/ajax"
        self.endpoint = "http://192.168.43.183/ajax"

    def test_channelCount(self):
        response = requests.get(self.endpoint + "/pwm/channelCount", timeout=1)
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.json()["channelCount"], 4)

    def test_pwm(self):
        test_data = [500, 1000, 1500, 2000]
        response = requests.post(self.endpoint + "/pwm/asArray", json=test_data, timeout=5)
        self.assertEqual(response.status_code, 200);

        response = requests.get(self.endpoint + "/pwm/asArray", timeout=5)
        self.assertEqual(test_data, response.json())
