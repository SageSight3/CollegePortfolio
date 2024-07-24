function wawa() {
	let in1 = document.getElementById("wa").value;
	let in2 = document.getElementById("wet").value;
	if ("" == in1 || "" == in2) {
		alert("I humbly request numbers");
	} else {
		let water = parseInt(in1);
		let dry = parseInt(in2);
		let result = 0;
		for (let iteration = 0; iteration < water + dry; iteration++) {
			result = result + iteration + water + dry;
		}
		
		if (result % 2 == 0) {
			document.getElementById("sand").innerHTML = "Surfers were not healthy :(";
		} else {
			document.getElementById("sand").innerHTML = "Surfers were healthy :)";
		}
	}
}
	