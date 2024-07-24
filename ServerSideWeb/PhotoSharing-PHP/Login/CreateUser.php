<?php
	require("LoginCheck.php");
	if($_SESSION["admin"] == false) {
		echo "I SMEL SHENANIGANS";
		echo "<a href='Protected.php'><p>Home</p></a>";
		exit(0);
	}
	
	echo "<!DOCTYPE html>
			<html>
				<head>
					<title>Create User</title>
				</head>
				<body>
					<h3>Add a new user</h4>
					<form action='CreateUser.php' method='POST'>
						<label for='newUser'>Enter username: </label>
						<input type='text' require='required' id='newUser' name='newUser'><br>
						<label for='newUserPW'>Enter password: </label>
						<input type='password' required='required' id='newUserPW' name='newUserPW'><br>
						<label for='confirmPW'>Confirm password: </label>
						<input type='password' required='required' id='confirmPW' name='confirmPW'><br>		
						<input type='submit' value='Add user'>
					</form>
					<a href='Protected.php'><p>Home</p></a>
				</body>
			</html>";

	@$newUser = $_REQUEST['newUser'];
	@$newUserPW = $_REQUEST['newUserPW'];
	@$confirmPW = $_REQUEST['confirmPW'];
	
	$hasWhiteSpace = preg_match('/\W/', $newUser, $matches);
	if ($matches) {
		echo "Username can't have spaces";
		exit(0);
	}
	
	if($newUserPW != $confirmPW) {
		echo "<p>Passwords don't match</p><br>";
		exit(0);
	}
	
	try {
		$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
		$userCheck = $dbHandle->prepare("SELECT * from SageLogin where username=?");
		if ($userCheck->execute(array($newUser))) {
			if ($userCheck->rowCount() == 0) {
				$hashedPW = hash('sha256', $newUserPW);
				$insert = $dbHandle->prepare("INSERT INTO SageLogin (username, password) VALUES (?, ?)");
				if ($insert->execute(array($newUser, $hashedPW))) {
					echo $newUser . " has been added";
				} else {
					echo "I V SAD INSERT FAILED";
				}
			} else {
				echo "Username has been taken";
			}
		} else {
			echo "USER CHECK NU WORK";
		}
	}catch (Exception $e) {
		"Error: " . $e->getMessage() . "<br>";
	}
?>