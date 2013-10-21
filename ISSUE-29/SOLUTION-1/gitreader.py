"""
  Olimex WPC #29 - Extract emails from GitHub

  This program uses the GitHub API to retrieve email addresses from GitHub.
  Without authentication, it is rate limited to 60 request per hour.
  With basic authentication (i.e you supply a GitHub username and password),
  the limit is increased to 5000 requests per hour.

  Output:
  - Internal state is preserved in file state.p
  - Retrieved logins and emails are recorded (tab separated) in mail_addresses.txt

"""

import base64
import datetime
import json
import httplib
import pickle
import re
import sys
import time

class GitReader:
	def __init__(self, username = None, password = None):
		self.done = False
		self.status = 200
		self.next_page = '/users'
		self.users = []
		self.ratelimit_reset = datetime.datetime.utcnow() + datetime.timedelta(seconds=600)
		self.remaining = 0
		try:
			f = open('state.p', 'r')
			try:
				self.next_page = pickle.load(f)
				self.users = pickle.load(f)
				self.ratelimit_reset = pickle.load(f)
				self.remaining = pickle.load(f)			
			except EOFError:
				pass
			finally:
				f.close()
		except IOError:
			pass

		if username is not None and password is not None:
			self.headers = {}
			authheader = "Basic {0}".format(base64.encodestring('{0}:{1}'.format(username, password)))
			self.headers['Authorization'] = authheader
		else:
			self.headers = None

	def save(self):
		"""Save the current state of the object.""" 
		try:
			f = open('state.p', 'w')
			try:
				pickle.dump(self.next_page, f)
				pickle.dump(self.users, f)
				pickle.dump(self.ratelimit_reset, f)
				pickle.dump(self.remaining, f)
			finally:
				f.close()
		except IOError:
			pass

	def request_url(self, url):
		"""Perform a GitHub api request"""
		headers = None
		body = None
		connection = httplib.HTTPSConnection('api.github.com')
		if self.headers is None:
			connection.request('GET', url)
		else:
			connection.request('GET', url, headers = self.headers)
		response = connection.getresponse()
		if response.status == 200:
			headers = response.getheaders()
			body = response.read()
			if headers is not None:
				self.parse_headers(headers)
			else:
				self.remaining = 0
				self.ratelimit_reset = datetime.datetime.utcnow() + datetime.timedelta(seconds=60)
		connection.close()	
		return body

	def parse_headers(self, headers):
		"""Parse the headers returned by a GitHub api request"""
		headers = eval(str(headers))
		for item in headers:
			(a,b) = item
			if a == 'x-ratelimit-reset':
				self.ratelimit_reset = datetime.datetime.utcfromtimestamp(float(b))
			elif a == 'x-ratelimit-remaining':
				self.remaining = int(b)
			elif a == 'link':
				r = re.search('<([^>]+)>\s*;\s*rel="next"',b)
				if r:
					r2 = re.search('/users\?since=\d+', r.group(1))
					if r2:
						self.next_page = r2.group(0)
					else:
						self.done = True

	def get_rate_limit(self):
		"""Retrieve the GitHub rate limit"""
		self.request_url('/rate_limit')

	def get_next_page(self):
		"""Retrieve a list of users and the url of the next page"""
		body = self.request_url(self.next_page)
		if body is not None:
			self.parse_users(body)
			self.remaining -= 1
			print 'Retrieved {0} logins'.format(len(self.users))
		if len(self.users) == 0:
			self.done = True
		self.save()

	def parse_users(self, body):
		"""Extract the individual logins from a list of users"""
		j = json.loads(body)
		for item in j:
			if 'login' in item:
				self.users.append(item['login'])

	def get_next_user(self, login):
		"""Retrieve the information pertaining to a single user"""
		body = self.request_url("/users/{0}".format(login))
		if body is not None:
			self.extract_email(body)
			self.users.remove(login)
			self.remaining -=1
		self.save()

	def extract_email(self, body):
		"""Extract the email address of a specific user and store it in a text file"""
		j = json.loads(body)
		try:
			mailfile = open('mail_addresses.txt', 'a')
			try:
				user = None
				mail = None
				if 'login' in j and j['login'] is not None:
					mailfile.write(j['login'])
					user = j['login']
				else:
					mailfile.write('<unknown>')
				mailfile.write('\t')
				if 'email' in j and j['email'] is not None:
					if j['email'] != '':
						mailfile.write(j['email'])
						mail = j['email']
					else:
						mailfile.write('<unknown>')
						mail = None
				else:
					mailfile.write('<unknown>')
				mailfile.write('\n')
				if user is not None and mail is not None:
					print '-> Retrieved address {0} for user {1}'.format(mail, user)
				elif user is not None and mail is None:
					print '-> No email for user {0}'.format(user)
				elif user is None and mail is not None:
					print '-> Retrieved address {0} for unknown user'.format(mail)
			finally:
				mailfile.close()
		except IOError:
			print 'Error writing file "mail_addresses.txt"'

	def can_retrieve(self):		
		"""Verify that rate limit has not been exceeded"""
		if self.remaining > 0:
			return True
		else:
			while self.remaining <= 0:
				self.get_rate_limit()
				if self.remaining > 0:
					return True
				else:
					now = datetime.datetime.utcnow()
					if self.ratelimit_reset > now:
						delay = (self.ratelimit_reset - now).total_seconds()
					else:
						delay = 0
					print 'Rate limit - sleeping until {0!s}\n'.format(self.ratelimit_reset)
					time.sleep(delay)				 											
		
	def get_userblock(self):
		"""Retrieve a page of users and get the next page."""
		while self.users:
			if self.can_retrieve():
				self.get_next_user(self.users[0])
		if self.can_retrieve():
			self.get_next_page()
				
	def go(self):
		"""Retrieve users until done"""
		while not self.done:
			#self.done = True
			if self.status != 200:
				print 'Status {0} - sleeping {1} seconds\n'.format(self.status, 60)
				time.sleep(60)
			else:
				self.get_userblock()
	
username = None
password = None
	
print 'Enter your GitHub username and password'
print 'or press <enter> to continue unauthenticated'

username = raw_input('Username: ')
if username:
	password = raw_input('Password: ')

if username == '' or password == '':
	g =	GitReader()
else:
	g = GitReader(username,password)
g.go()
