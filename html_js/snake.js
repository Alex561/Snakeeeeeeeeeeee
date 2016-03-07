

$(document).ready(function(){
	//Canvas stuff
	//console.log('what the shit bro');
	
	var canvas = $("#canvas")[0];
	var ctx = canvas.getContext("2d");
	var w = $("#canvas").width();
	var h = $("#canvas").height();
	
	//Lets save the cell width in a variable for easy control
	var cw = 10;
	var d1;
	var d2;
	var food;
	var score1;
	var score2;
	var old_score1;
	var old_score2;
	var p1ID;
	var p2ID;
	var game_over;
	var snake_array1; //snake_array1 is *this* client's snake
	var snake_array2; //snake_array2 is the other client's snake
	var official_snake1; //official version of this client's snake, consistent w/ server
	var official_snake2; //official version of other client's snake, consistent w/ server
	var Server; 
	var total_latency = 0;
	var latency_samples = 0;

	function connect(){
    var ip = prompt("Enter IP address to connect to", "127.0.0.1");
	var port = prompt("Enter port", "44222");
	p1ID = prompt("Enter name ", "Salad Snek");
	console.log(p1ID + " is player 1");

	
	Server = new FancyWebSocket('ws://' + ip + ':' + port);
	Server.connect(); 
	
	//send Client Initialization packet w/ ID's 
	
	Server.bind('open', function(){
		Server.send("ID", "C_INIT;" + p1ID);
		//server should probably send a packet upon connection that tells each client both player names so t
	})
}

connect();



	function make_snake(hx,hy,tx,ty){
		var snake_array = [];
		if(hx == tx){
				if(hy > ty){
					for(var i = hy; i >= ty ; i--){
						snake_array.push({x: hx, y: i});
					}
				}
				else{
					for(var i = hy; i <= ty ; i++){
						snake_array.push({x: hx, y: i});
					}

				}

			}
			else{
				if(hx > tx){
					for(var i = hx; i >= tx ; i--){
						snake_array.push({x: i, y: hy});
					}
				}
				else{
					for(var i = hx; i <= tx ; i++){
						snake_array.push({x: hx, y: i});
					}

				}

			}
		return snake_array;

	}

	function snake_me_up_before_you_go_go(hx,hy,score,oldscore,snake_array){
		if(score > oldscore){
			var tail = {x:hx, y:hy};

		}
		else{
			var tail = snake_array.pop();
			tail.x = hx;
			tail.y = hy;
		}
		snake_array.unshift(tail);
		return snake_array;
	}

	function copy_snake(snake_array) {
	    var new_snake = [];
	    for (var i = 0; i < snake_array.length; i++) {
	        var to_add = new Object();
	        to_add.x = snake_array[i].x;
	        to_add.y = snake_array[i].y;
	        new_snake.push(to_add);
	    }
	    return new_snake;
	}
	/*Server.bind('message', function( payload ) {
	console.log("Server says: " + payload);
	var semis = payload.split(";");
		if(semis[0] == "S_INIT"){
			
			var head1x = parseInt(semis[1]);
			var head1y = parseInt(semis[2]);
			var tail1x = parseInt(semis[3]);
			var tail1y = parseInt(semis[4]);
			snake_array1 = make_snake(head1x,head1y,tail1x,tail1y);
			var head2x = parseInt(semis[5]);
			var head2y = parseInt(semis[6]);
			var tail2x = parseInt(semis[7]);
			var tail2y = parseInt(semis[8]);

			snake_array2 = make_snake(head2x,head2y,tail2x,tail2y);
			food = {
				x: parseInt(semis[9]),
				y: parseInt(semis[10]),
				};
			
			p2ID = semis[11];
			d1 = semis[12];
			d2 = semis[13];
			paint();
			if (typeof game_loop != "undefined") clearInterval(game_loop);
			game_loop = setInterval(paint, 30);
			}


			
		else if(semis[0] == "S_UP"){
			old_score1 = score1;
			old_score2 = score2;
			head1x = parseInt(semis[1]);
			head1y = parseInt(semis[2]);
			head2x = parseInt(semis[3]);
			head2y = parseInt(semis[4]);
			food = {
				x: parseInt(semis[5]),
				y: parseInt(semis[6]),
			};
			score1 = parseInt(semis[7]);
			score2 = parseInt(semis[8]);


			snake_array1 = snake_me_up_before_you_go_go(head1x,head1y,score1,old_score1,snake_array1);
			snake_array2 = snake_me_up_before_you_go_go(head2x,head2y,score2,old_score2,snake_array2);
			d1 = semis[9];
			paint();
		}
		else if(semis[0] == "S_TIMESTAMP"){
			var t3 = Date.now();
			//var t3 = now.parse();
			var t0 = semis[1];
			var t1 = semis[2];
			var t2 = semis[3];
			
			console.log(t3);
			console.log(t3 - t2);
			
			total_latency += ((t3-t0)-(t2-t1));
			latency_samples++;



		}

	});*/

/*Server.bind('close',function({
	
	quit = true;
});*/

var iFrequency = 1000; // expressed in miliseconds
var myInterval = 0;

// STARTS and Resets the loop if any
function sendTime()
{
    var now = Date.now();
   // var utc_now = Date.UTC(now.getUTCyear)
    Server.send("time bitch", "C_TIMESTAMP;" + now);
}

function startLoop() {
    if(myInterval > 0) clearInterval(myInterval);  // stop
    myInterval = setInterval( sendTime, iFrequency );  // run
}
Server.bind('close', function(){
    clearInterval(myInterval);
    clearInterval(game_loop);
});


startLoop();

	Server.bind('message', function( payload ) {
	console.log("Server says: " + payload);
	var semis = payload.split(";");
		if(semis[0] == "S_INIT"){
			
			var head1x = parseInt(semis[1]);
			var head1y = parseInt(semis[2]);
			var tail1x = parseInt(semis[3]);
			var tail1y = parseInt(semis[4]);
			official_snake1 = make_snake(head1x, head1y, tail1x, tail1y);
			var snakeinitial = "initial: ";
			for (var i = 0; i < official_snake1.length; i++) {
			    snakeinitial = snakeinitial + "x: " + official_snake1[i].x + " y: " + official_snake1[i].y + ". ";

			}
			console.log(snakeinitial);
			var snake1 = "copied initial: ";
			for (var i = 0; i < official_snake1.length; i++) {
			    snake1 = snake1 + "x: " + official_snake1[i].x + " y: " + official_snake1[i].y;

			}
			console.log(snake1);
			snake_array1 = copy_snake(official_snake1);
			//official_snake1 = snake_array1.slice();
			var head2x = parseInt(semis[5]);
			var head2y = parseInt(semis[6]);
			var tail2x = parseInt(semis[7]);
			var tail2y = parseInt(semis[8]);

			official_snake2 = make_snake(head2x, head2y, tail2x, tail2y);
			snake_array2 = copy_snake(official_snake2);
			food = {
				x: parseInt(semis[9]),
				y: parseInt(semis[10]),
				};
			//paint();
			var snake8 = "copied initial: ";
			for (var i = 0; i < official_snake1.length; i++) {
			    snake8 = snake8 + "x: " + official_snake1[i].x + " y: " + official_snake1[i].y;

			}
			console.log(snake1);

			p2ID = semis[11];
			if (typeof game_loop != "undefined") clearInterval(game_loop);
			game_loop = setInterval(paint, 600);
			d1 = semis[12];
			d2 = semis[13];
			}


			
		else if(semis[0] == "S_UP"){
			old_score1 = score1;
			old_score2 = score2;
			head1x = parseInt(semis[1]);
			head1y = parseInt(semis[2]);
			head2x = parseInt(semis[3]);
			head2y = parseInt(semis[4]);
			food = {
				x: parseInt(semis[5]),
				y: parseInt(semis[6]),
			};
			score1 = parseInt(semis[7]);
			score2 = parseInt(semis[8]);
			d2 = semis[9];

			//onsole.log("Before update " + snake_array1[0].x + "," + snake_array1[0].y);
			official_snake1 = snake_me_up_before_you_go_go(head1x, head1y, score1, old_score1, official_snake1);
		    //snake_array1 = official_snake1.slice();
			var snake1 = "before: ";
			for (var i = 0; i < official_snake1.length; i++) {
			    snake1 = snake1 + "x: " + official_snake1[i].x + " y: " + official_snake1[i].y;

			}
			console.log(snake1);
			snake_array1 = copy_snake(official_snake1);
			var snakeafter = "after: ";
			for (var i = 0; i < snake_array1.length; i++) {
			    snakeafter = snakeafter + "x: " + snake_array1[i].x + " y: " + snake_array1[i].y + ". ";

			}
			console.log(snakeafter);
			official_snake2 = snake_me_up_before_you_go_go(head2x,head2y,score2,old_score2,official_snake2);
			snake_array2 = copy_snake(official_snake2);
			
			paint();
		}
		else if (semis[0] == "S_TIMESTAMP") {
		    var t3 = Date.now();
		    //var t3 = now.parse();
		    var t0 = semis[1];

		    var t1 = semis[2];
		    var t2 = semis[3];

		    //console.log(t3);
		    //console.log(t3 - t2);

		    total_latency += ((t3 - t0) - (t2 - t1));
		    latency_samples++;



		}


	});

	//Lets paint the snake now
	function paint()
	{
		//To avoid the snake trail we need to paint the BG on every frame
	    //Lets paint the canvas now
	   // console.log(snake_array1.length);
		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, w, h);
		ctx.strokeStyle = "black";
		ctx.strokeRect(0, 0, w, h);

		var nx1 = snake_array1[0].x;
		var ny1 = snake_array1[0].y;
		var nx2 = snake_array2[0].x;
		var ny2 = snake_array2[0].y;

		

		if (d1 == "RIGHT") nx1++;
		else if (d1 == "LEFT") nx1--;
		else if (d1 == "UP") ny1--;
		else if (d1 == "DOWN") ny1++;

		if (d2 == "RIGHT") nx2++;
		else if (d2 == "LEFT") nx2--;
		else if (d2 == "UP") ny2--;
		else if (d2 == "DOWN") ny2++;

		var tail1 = snake_array1.pop(); //pops out the last cell
		tail1.x = nx1; tail1.y = ny1;

		var tail2 = snake_array2.pop(); //pops out the last cell
		tail2.x = nx2; tail2.y = ny2;
		

		snake_array1.unshift(tail1); //puts back the tail as the first cell
		snake_array2.unshift(tail2); //puts back the tail as the first cell
		
		/*for(var i = 0; i < official_snake1.length; i++)
		{
			var c = official_snake1[i];
			//Lets paint 10px wide cells
			paint_cell(c.x, c.y,"p1");
		}

		for(var i = 0; i < official_snake2.length; i++)
		{
			var c = official_snake2[i];
			//Lets paint 10px wide cells
			paint_cell(c.x, c.y,"p2");
		}*/


		var snakeafter = "in paint: ";
		for (var i = 0; i < snake_array1.length; i++) {
		    snakeafter = snakeafter + "(" + snake_array1[i].x + ", " + snake_array1[i].y + ") ";
		}
		console.log(snakeafter);

		for (var i = 0; i < snake_array1.length; i++) {
		   

		    var c = snake_array1[i];
		    //Lets paint 10px wide cells
		    paint_cell(c.x, c.y, "p1");
		    //console.log("painted" + c.x + "," + c.y);
		    
		}

		for (var i = 0; i < snake_array2.length; i++) {
		    var c = snake_array2[i];
		    //Lets paint 10px wide cells
		    paint_cell(c.x, c.y, "p2");
		}
		


        
		var latency = total_latency/latency_samples;
		//Lets paint the food
		paint_cell(food.x, food.y, "food");
		var score_text1 = p1ID + ": " + score1;
		var score_text2 = p2ID + ": " + score2;
		ctx.font = ("10px Verdana");
		ctx.fillText("Average Latency: "+ latency, 5,10);
		ctx.fillText(score_text1, 5, h-5);
		ctx.fillText(score_text2, w-60, h-5); 
		//Lets paint the score
	}
	
	//Lets first create a generic function to paint cells
	function paint_cell(x, y, type)
	{
		if(type == "food") ctx.fillStyle = "#FF0000";
		else if(type == "p2") ctx.fillStyle = "#00FF00";
		else if(type == "p1") ctx.fillStyle = "#0000FF";
		ctx.fillRect(x*cw, y*cw, cw, cw);
		ctx.strokeStyle = "white";
		ctx.strokeRect(x*cw, y*cw, cw, cw);
	}
	
	

	
	//Lets add the keyboard controls now
	$(document).keydown(function(e){
		var key = e.which;
		//We will add another clause to prevent reverse gear
		//if(key == "32" && game_over) init();
		if(key == "37"){ Server.send("input","C_INPUT;LEFT"); d1 = "LEFT";}
		else if(key == "38" ){ Server.send("input","C_INPUT;UP"); d1 = "UP";}
		else if(key == "39" ){ Server.send("input","C_INPUT;RIGHT"); d1 = "RIGHT";}
		else if(key == "40" ){ Server.send("input","C_INPUT;DOWN"); d1 = "DOWN";}
		

	
    // This is where you do whatever you want with the time:
  
		//The snake is now keyboard controllable
	})
});
	


	
	
	
	


