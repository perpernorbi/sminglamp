import unittest
import requests
import json


class TestPwmApi(unittest.TestCase):
    def setUp(self):
        self.endpoint = "http://192.168.1.122/ajax"
#        self.endpoint = "http://192.168.43.183/ajax"

    def test_channelCount(self):
        response = requests.get(self.endpoint + "/pwm/channelCount", timeout=1)
        self.assertEqual(200, response.status_code)
        self.assertEqual(4, response.json())

    def test_pwm(self):
        test_data = [500, 1000, 1500, 2000]
        response = requests.post(self.endpoint + "/pwm/asArray", json=test_data, timeout=5)
        self.assertEqual(200, response.status_code);

        response = requests.get(self.endpoint + "/pwm/asArray", timeout=5)
        self.assertEqual(test_data, response.json())

    def test_testEndpoint(self):
        response = requests.get(self.endpoint + "/test", timeout=5)
        self.assertEqual([1,2,3], response.json())

    def test_setters(self):
        response = requests.post(self.endpoint + "/setBool", json=True, timeout=5)
        self.assertEqual(response.status_code, 200)

        response = requests.post(self.endpoint + "/setInt", json=13, timeout=5)
        self.assertEqual(response.status_code, 200)

        response = requests.post(self.endpoint + "/setString", json="Hello Json World", timeout=5)
        self.assertEqual(response.status_code, 200)
