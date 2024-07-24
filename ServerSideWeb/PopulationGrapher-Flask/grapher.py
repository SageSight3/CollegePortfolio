from flask import *
import os
import numpy as np
import io
import base64
import mysql.connector
import matplotlib.pyplot as plt #will need another install on server to work
import matplotlib
matplotlib.use('Agg')
app = Flask(__name__)

#why would half of the things in this program by default -_- looking at  buffered cursor and half the plt attributes
#what's Pandas DatadFrame?

app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

sqlCon = mysql.connector.connect(
    host = "localhost",
    username = "nations",
    password = "nations!",
    database = "nations"
)
    
def generateGraph(num):
    #if not buffered, will error after a while when changing numbers quickly
    #noticed at around num between 230-250, if I'm remembering right
    #was holding down up arrow to increment num from 1 to 268 
    sqlCur = sqlCon.cursor(buffered=True) #https://stackoverflow.com/questions/29772337/python-mysql-connector-unread-result-found-when-using-fetchone
    
    query = "SELECT name, Pop FROM nations ORDER BY Pop DESC LIMIT %s"
    numOfNations = (num,)
    sqlCur.execute(query, numOfNations)
    results = sqlCur.fetchall()
    
    countries = []
    for result in range(0, num):
        countries.append(results[num-1-result][0])

    populations = []
    for result in range(0, num): 
        populations.append(results[num-1-result][1])
    
    ySpacing = np.arange(len(countries)) #https://numpy.org/doc/stable/reference/generated/numpy.arange.html
    xSize = 6.4*(1+num/400) #figsize? complained about it not being a float in setting size
    plt.figure(figsize=(xSize, num/2)) #https://stackoverflow.com/questions/44631424/change-horizontal-barplot-sizes-matplotlib
    plt.barh(countries, populations, align='center')
    
    #https://stackoverflow.com/questions/20214497/annoying-white-space-in-bar-chart-matplotlib-python
    #https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.ylim.html
    plt.ylim([-1, len(countries)]) #eliminates excess whitespace above and below bars, -1 keeps bottom bar from being cut off
    plt.yticks(ySpacing, countries)
    plt.title("Largest " + str(num) + " Nations by Population")
    plt.xlabel('Population')
    plt.ylabel('Country')
    
    return plt

@app.route('/invalidNum')
def invalidNum():
    invalidNumMsg = "<b>Enter a number between 1 and 268</b>"
    return invalidNumMsg
    
@app.route('/query')
def getQuery():
    return render_template("query.html")

@app.route('/nationPops/<int:num>')
def getGraph(num):
    if num < 1 or num > 268 or not isinstance(num, int):
        return redirect(url_for('invalidNum'))
    
    popGraph = generateGraph(num)
    s = io.BytesIO()
    popGraph.savefig(s, format='png', bbox_inches = "tight")
    popGraph.close()
    
    s = base64.b64encode(s.getvalue()).decode("utf-8").replace("\n", "")
    return '<img align="left" src="data:image/png;base64,%s">' % s
    
#    return render_template('popGraph.html', s = s, debug = num) 
    
    

if __name__ == '__main__':
   app.run('0.0.0.0', debug = True)