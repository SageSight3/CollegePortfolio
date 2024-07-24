<?php
	require("LoginCheck.php");
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Home</title>
	</head>
	<body>
		<ul>
			<li><a href='Users.php'><button type='button'>Users</button></a></li>
			<li><a href='CreateUser.php'><button type='button'>Create User</button></a></li>
			<li><a href='DeleteUser.php'><button type='button'>Delete User</button></a></li>
			<li><a href='V1.php'><button type='button'>V1</button></a></li>
			<li><a href='Logout.php'><button type='button'>Log out</button></a></li>
			<li><a href='../AddPhoto.php'><button type='button'>Upload Photo</button></a></li>
			<li><a href='../PictureSearch.php'><button type='button'>Picture Search</button></a></li>
			<li><a href='../Random.php'><button type='button'>Random Image Search</button></a></li>
		</ul>
	</body>
</html>";
?>