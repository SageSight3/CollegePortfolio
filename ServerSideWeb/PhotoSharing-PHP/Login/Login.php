<?php
	session_start();
	
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Login</title>
	</head>
	<body>
		<form action='Login.php' method='POST'>
			<label for='username'>Username: </label>
			<input type='text' required='required' id='username' name='username'><br>
			<label for='password'>Password: </label>
			<input type='password'required='required' id='password' name='password'><br>		
			<input type='submit' value='Log in'>
		</form>
	</body>
</html>";

	@$username = $_REQUEST['username'];
	@$password = $_REQUEST['password'];
	
	if (empty($username) || empty($password)) { 
		echo "Enter username and password"; 
	} else {
		try {
			$hashedPW = hash('sha256', $password);
			
			$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
			#print("junk<br>"); debug
#			$login = $dbHandle->prepare("SELECT * from SageLogin where username='?' and password='?'"); //prepare means run as only one statement?
#			if ($login->execute(array($username, $hashedPW))){
			$login = $dbHandle->prepare("SELECT * from SageLogin where username=? and password=?"); //prepare means run as only one statement?
			if ($login->execute(array($username, $hashedPW))){
				if ($login->rowCount() == 1) {
					$_SESSION["logged_in"] = True;
					$_SESSION["admin"] = False;
					if($username == "SageSight") {
						$_SESSION["admin"] = True;
						//echo "Admin logged in";
					}
					header("Location: Protected.php");
				}
				else
				{					
					echo "<p>Login failed</p>";
				}
			}
			else
			{
				echo "<p>THIS CODE SMELS LIKE THE BAD CHEESE</p>";
			}	
		} catch (Exception $e) {
			echo "Error " . $e->getMessage() . "</br>";
			die();
		}
	}
?>