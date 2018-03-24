import os
import BaseHTTPServer
import SimpleHTTPServer
import urllib

class RequestHandler(BaseHTTPServer.BaseHTTPRequestHandler):
  Page = '''
        <html>
        <body>
        <p>This is a simple server for Ray Tracer</p>
        </body>
        </html>
    '''

  def do_GET(self):
      self.send_response(200)
      self.send_header("Content-Type", "text/html")
      self.send_header("Content-Length", str(len(self.Page)))
      self.send_header("Access-Control-Allow-Origin", "*")
      self.end_headers()
      self.wfile.write(self.Page)
      print("GET")

  def do_POST(self):
      data = self.rfile.read(int(self.headers['content-length']))  
      data = urllib.unquote(data).decode("utf-8", 'ignore')
      self.send_response(200)
      self.send_header("Access-Control-Allow-Origin", "*")
      self.send_header("Access-Control-Expose-Headers", "Access-Control-Allow-Origin");
      self.send_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
      self.end_headers()
      self.wfile.write("success")
      print (data)
      print("POST")
      with open('post_data.json', 'w') as f:
        f.write(data)
      main = "./raytracer post_data.json"
      os.system(main)


  def do_OPTIONS(self):
      self.send_response(200)
      self.send_header("Access-Control-Allow-Origin", "*")
      self.send_header("Access-Control-Expose-Headers", "Access-Control-Allow-Origin");
      self.send_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
      self.end_headers()

# -------------------------------

if __name__ == '__main__':
    serverAddress = ('', 8080)
    Handler = RequestHandler
    server = BaseHTTPServer.HTTPServer(serverAddress, Handler)
    server.serve_forever()

print("finished")