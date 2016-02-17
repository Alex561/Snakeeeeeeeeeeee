
 







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
	var Server; 

	function connect(){
    var ip = prompt("Enter IP address to connect to", "127.0.0.1");
	var port = prompt("Enter port", "44222");
	p1ID = prompt("Enter name ", "Salad Snek");
	//p2ID = prompt("Enter name for Player 2", "Liquid");
	console.log(p1ID + " is player 1");
	//console.log(p2ID + " is player 2");
	
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

	Server.bind('message', function( payload ) {
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
			paint();
			p2ID = semis[11];
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
			paint();
		}

	});

	
	

	//Lets paint the snake now
	function paint()
	{
		//To avoid the snake trail we need to paint the BG on every frame
		//Lets paint the canvas now
		ctx.fillStyle = "white";
		ctx.fillRect(0, 0, w, h);
		ctx.strokeStyle = "black";
		ctx.strokeRect(0, 0, w, h);
		
		
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
		var score_text1 = p1ID + ": " + score1;
		var score_text2 = p2ID + ": " + score2;
		ctx.font = ("10px Verdana");
		ctx.fillText(score_text1, 5, h-5);
		ctx.fillText(score_text2, w-150, h-5); 
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
		if(key == "37") Server.send("input","C_INPUT;LEFT");
		else if(key == "38" ) Server.send("input","C_INPUT;UP");
		else if(key == "39" ) Server.send("input","C_INPUT;RIGHT");
		else if(key == "40" ) Server.send("input","C_INPUT;DOWN");
		//The snake is now keyboard controllable
	})
	
	
});	
	
	
	
	


