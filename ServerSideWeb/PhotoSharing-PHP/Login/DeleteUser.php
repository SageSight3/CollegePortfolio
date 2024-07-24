<?php
	error_reporting(0); //have no idea how suppress for each loop warning alone
	require("LoginCheck.php");
	if($_SESSION["admin"] == false) {
		echo "I SMEL SHENANIGANS";
		echo "<a href='Protected.php'><p>Home</p></a>";
		exit(0);
	}
	
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Delete User</title>
	</head>
	<body>
		<h4>Select who you want to remove from the database</h4>
		<form action='DeleteUser.php' method='POST'>";
		
	//for help with php array input, //https://html.form.guide/php-form/php-form-checkbox/
	$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	foreach($dbHandle->query('SELECT username from SageLogin') as $user) {
		echo "		<input type='checkbox' id='users[]' name='users[]' value='". $user['username'] . "'>
		<label for='users[]'>" . $user['username'] . "</label><br>"; 
	}
		
	echo "	<input type='submit' value='Delete'>
	</form>
	<a href='Protected.php'><p>Home</p></a>
	</body>
</html>";

	$delUsers = isset($_REQUEST['users']) ? $_REQUEST['users']: ''; #https://stackoverflow.com/questions/72714864/getting-error-undefined-array-key-in-php-file-with-html-forms
	#echo $delUsers; debug
	foreach($delUsers as $name) {
		#echo $name; debug
		if ($name == "SageSight") {
			echo "Admin can't be deleted";
			exit(0);
		}
		$delete = $dbHandle->prepare("DELETE FROM SageLogin WHERE username=?");
		if($delete->execute(array($name))) {
			echo $name . " has been removed<br>"; //commented out because consistency in programming languages is a lie
			//i don't know why the for update just randomly broke, despite me not changing code, i love this
			//echo "<meta http-equiv='refresh' content='0'>"; //https://stackoverflow.com/questions/10643626/refresh-page-after-form-submitting
		} else {
			echo "DEWETE FAIWED";
		}
	}
?>