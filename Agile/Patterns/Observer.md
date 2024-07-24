# Observer

**Name:** Observer

**Forces**\
 Since in layered architecture, no layer should know anything of the layers above them, the responsiility of information retrieval falls onto the higher of any two that need to interact with each other. The reasons for this are for this include optimization of code within lower layers, as well as ease of maintenence should upper layers be modified.

For example, say we have a table in an HTML document that needs to update (GUI layer), based on the values of a table in an SQL database. One way that could be implemented could be to have a script write to the SQL table's data to the HTML's as needed, through something like messing with the HTML's DOM in JavaScript, or something else similar (Application layer).

HTML:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="client.js"></script>
    <title>SQL Table Data</title>
</head>
<body>
    <table id="sqlData">
        ...
    </table>
</body>
</html>
```

client.js:

```js

function getData() {
    //get SQL table data
}

function parseTable(sqlData) {
    //format SQL into HTML
}

function updateTable() {
    let htmlTable = parseTable(getData());
    document.getElementById("sqlData").innerHTML = htmlTable;
}

//update html table every second
let updater = setInterval(updateTable, 1000);
```

The problem with this is that any if change made were to be to the HTML, that change has to be reflected in ```client.js```. If say, we decided the sql data would be better displayed as a list, not only do we need to reformat the HTML, our ```parseTable()``` method is now redundant, and a whole new method would be needed to parse the SQL data.

Furthermore, there's a whole extra step we're having to take in the JS, that wouldn't be needed if we weren't worrying about readying the SQL data to be displayed in the HTML.

**Resolution**\
 Instead of forcing the lower layer to conform to the needs of the upper. Have the upper *observe* the lower and change it's value, as needed based off what it sees.

For the purpose of this example, we can achieve this through the use of a Vue app.

HTML:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src='https://unpkg.com/vue@3/dist/vue.global.js'></script>
    <script defer src="client.js"></script>
    <title>SQL Table Data</title>
</head>
<body>
    <div id="app">
        <table>
            <tr><th>SQL Data</th></tr>
            <div id="sqlData" v-for="(data, index) of sqlData" :key="data.dataID">
                <span>
                    <tr v-for="(element, entryIndex) of data" :key="element.id">
                        <span>
                            <td v-bind:value="element"></td>
                        </span>
                    </tr>
                </span>
            </div>
        </table>
    </div>
</body>
</html>
```

Here, we use a mix of HTML Vue attributes, to represent the values of an array in our Vue app, called ```sqlData```, in a desired format, in this case a table. 

client.js:

```js
let myApp = Vue.createApp({
    data () {
        sqlData: [],
        table: null;
    },
    methods: {
        updateSQLData() {
            let updatedData = function () {
                //retrieve data from SQL database
            };

            //give each row of updatedData and their columns unique ids
            for(data of updatedData) {
                data.dataID = Symbol();
                for (element of data) {
                    element.id = Symbol();
                }
            }

            this.sqlData = updatedData;
        },
    }
}).mount("#app");

//updates myApp.sqlData once a second
let updater = setInterval(myApp.updateSQLData, 1000);
```

Notice that if we were then to alter the HTML, as long as we continued to reference ```sqlData``` in the Vue app, the ```Vue``` app could be left completely alone. The GUI layer has been effectively contained to exclusivelely the files responsible for the programs visual presentation, while also reducing the amount of work our JS is responsible for.

**Following Patterns**

[MVC - Model View Controller](./MVC.md)