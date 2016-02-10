
 







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
	var p1ID;
	var p2ID;
	var game_over;
	var snake_array1; //keep, initialize with S_INIT packet's data 
	var snake_array2;
	var Server; 

	function connect(){
    var ip = prompt("Enter IP address to connect to", "127.0.0.1");
	var port = prompt("Enter port", "");
	p1ID = prompt("Enter name for Player 1", "Solid");
	p2ID = prompt("Enter name for Player 2", "Liquid");
	console.log(p1ID + " is player 1");
	console.log(p2ID + " is player 2");
	
	Server = new FancyWebSocket('ws://' + ip + ':' + port);
	Server.connect(); 
	
	//send Client Initialization packet w/ ID's 
	
	Server.bind('open', function(){
		Server.send("ID", "C_INIT;" + p1ID + ";" + p2ID);
	})

	Server.bind('message', function( payload ) {
	
	var splitshit = payload.split(";");
	score1 = parseInt(splitshit[0]);
	score2 = parseInt(splitshit[1]);

	console.log(payload);
    Server.send("echo", payload);
	});

	}
	connect();
    //sendMessage("SPaghetti", "knees weak, arms heavy, client's ready, mom's spaghetti");

	function sendMessage(msg){
    // Wait until the state of the socket is not ready and send the message when it is...
    waitForSocketConnection(Server, function(){
        console.log("message sent!!!");
        Server.send(msg);
    });
}

// Make the function wait until the connection is made...
function waitForSocketConnection(socket, callback){
    setTimeout(
        function () {
        	console.log(socket.readyState);
            if (socket.readyState === 1) {
                console.log("Connection is made")
                if(callback != null){
                    callback();
                }
                return;

            } else {
                console.log("wait for connection...")
                //waitForSocketConnection(socket, callback);
                setTimeout(waitForSocketConnection, 10);
            }

        }, 500); // wait 5 milisecond for the connection...
}

    
	
	//Lets create the snake now
	
	


	
	function init() //might get rid of this function altogether
	{
		d1 = "right"; //
		d2 = "left"; // 
		create_snake1();
		create_snake2();
		create_food(); //Now we can see the food particle
		//finally lets display the score
		score1 = 0;//keep
		score2 = 0;
		//Lets move the snake now using a timer which will trigger the paint function
		//every 60ms
		if(typeof game_loop != "undefined") clearInterval(game_loop);
		game_loop = setInterval(paint, 60);
		game_over = false;
	}
	init();
	
	function create_snake1()
	{
		var length = 5; //Length of the snake
		snake_array1 = []; //Empty array to start with
		for(var i = length-1; i>=0; i--)
		{
			//This will create a horizontal snake starting from the top left
			snake_array1.push({x: i, y:0});
		}
	}

	function create_snake2()
	{
		var length = 5; //Length of the snake
		snake_array2 = []; //Empty array to start with
		for(var i = length-1; i>=0; i--)
		{
			//This will create a horizontal snake starting from the top left
			snake_array2.push({x: 0, y:i});
		}
	}	
	//Lets create the food now
	function create_food()
	{
		food = {
			x: Math.round(Math.random()*(w-cw)/cw), 
			y: Math.round(Math.random()*(h-cw)/cw), 
		};
		//This will create a cell with x/y between 0-44
		//Because there are 45(450/10) positions accross the rows and columns
	}
	
	//Lets paint the snake now
	function paint()
	{
		//To avoid the snake trail we need to paint the BG on every frame
		//Lets paint the canvas now
		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, w, h);
		ctx.strokeStyle = "black";
		ctx.strokeRect(0, 0, w, h);
		
		//The movement code for the snake to come here.
		//The logic is simple
		//Pop out the tail cell and place it infront of the head cell
		var nx1 = snake_array1[0].x;
		var ny1 = snake_array1[0].y;
		var nx2 = snake_array2[0].x;
		var ny2 = snake_array2[0].y;
		//These were the position of the head cell.
		//We will increment it to get the new head position
		//Lets add proper direction based movement now
		if(d1 == "right") nx1++;
		else if(d1 == "left") nx1--;
		else if(d1 == "up") ny1--;
		else if(d1 == "down") ny1++;
		
		if(d2 == "right") nx2++;
		else if(d2 == "left") nx2--;
		else if(d2 == "up") ny2--;
		else if(d2 == "down") ny2++;	
		//Lets add the game over clauses now
		//This will restart the game if the snake hits the wall
		//Lets add the code for body collision
		//Now if the head of the snake bumps into its body, the game will restart
		if(nx1 == -1 || nx1 == w/cw || ny1 == -1 || ny1 == h/cw || check_collision(nx1, ny1, snake_array1) || nx2 == -1 || nx2 == w/cw || ny2 == -1 || ny2 == h/cw || check_collision(nx2,ny2,snake_array2)  || check_collision(nx1,ny1,snake_array2) || check_collision(nx2,ny2,snake_array1))
		{
			//restart game
			// add in shit right here to display who wins, probably dont restart? or maybe wait for an input 
			game_over = true;
			/*var winner;
			ctx.font="20px Verdana";

			if(score1 > score2) winner = "Player 1 wins!";
			else if(score2 > score1) winner = "Player 2 wins!";
			else winner = "It's a tie!";
			ctx.fillText("Game Over!\n" + winner + "\n Press Space to Restart" , 0, 0);
*/

			Server.send("ID", "C_INIT;" + p1ID + ";" + p2ID);
			init();

			//Lets organize the code a bit now.
			return;
		}
		
		//Lets write the code to make the snake eat the food
		//The logic is simple
		//If the new head position matches with that of the food,
		//Create a new head instead of moving the tail
		if(nx1 == food.x && ny1 == food.y)
		{
			var tail1 = {x: nx1, y: ny1};
			//score1++;
			Server.send("I ATE","FOOD;" + p1ID);
			//Create new food
			create_food();
		}
		else
		{
			var tail1 = snake_array1.pop(); //pops out the last cell
			tail1.x = nx1; tail1.y = ny1;
		}
		if(nx2 == food.x && ny2 == food.y)
		{
			var tail2 = {x: nx2, y: ny2};
			//score2++;
			Server.send("I ATE","FOOD;" + p2ID);
			//Create new food
			create_food();
		}
		else
		{
			var tail2 = snake_array2.pop(); //pops out the last cell
			tail2.x = nx2; tail2.y = ny2;
		}
		//The snake can now eat the food.
		
		snake_array1.unshift(tail1); //puts back the tail as the first cell
		snake_array2.unshift(tail2); //puts back the tail as the first cell
		
		for(var i = 0; i < snake_array1.length; i++)
		{
			var c = snake_array1[i];
			//Lets paint 10px wide cells
			paint_cell(c.x, c.y,"p1");
		}

		for(var i = 0; i < snake_array2.length; i++)
		{
			var c = snake_array2[i];
			//Lets paint 10px wide cells
			paint_cell(c.x, c.y,"p2");
		}
		
		//Lets paint the food
		paint_cell(food.x, food.y, "food");
		//Lets paint the score
		var score_text1 = "Player 1: " + score1;
		var score_text2 = "Player 2: " + score2;
		ctx.font = ("10px Verdana");
		ctx.fillText(score_text1, 5, h-5);
		ctx.fillText(score_text2, w-60, h-5); 
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
	
	function check_collision(x, y, array)
	{
		//This function will check if the provided x/y coordinates exist
		//in an array of cells or not
		for(var i = 0; i < array.length; i++)
		{
			if(array[i].x == x && array[i].y == y)
			 return true;
		}
		return false;
	}

	
	//Lets add the keyboard controls now
	$(document).keydown(function(e){
		var key = e.which;
		//We will add another clause to prevent reverse gear
		if(key == "32" && game_over) init();
		if(key == "37" && d1 != "right") d1 = "left";
		else if(key == "38" && d1 != "down") d1 = "up";
		else if(key == "39" && d1 != "left") d1 = "right";
		else if(key == "40" && d1 != "up") d1 = "down";
		if(key == "65" && d2 != "right") d2 = "left";
		else if(key == "87" && d2 != "down") d2 = "up";
		else if(key == "68" && d2 != "left") d2 = "right";
		else if(key == "83" && d2 != "up") d2 = "down";
		//The snake is now keyboard controllable
	})
	
	
});	
	
	
	
	


