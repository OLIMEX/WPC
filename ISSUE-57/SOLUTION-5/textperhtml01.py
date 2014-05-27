import lxml.html

h='''<html><head><title>Hello Title</title>
<head><body id="bodyid">
<div id="articlea">Hi</div>
<div id="bye">Bye bye</div>
</body></html>
'''

t=lxml.html.fromstring(h).text_content()
print 100.0*len(t)/len(h)