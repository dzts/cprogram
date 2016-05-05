<?php

for( $i=0;$i<100;$i++ ){
$swoole[$i] = new swoole_client(SWOOLE_SOCK_TCP,SWOOLE_SOCK_ASYNC);

$swoole[$i]->on("connect",function($cli){
	$cli->send("abcdefg");
	$cli->close();
});
$swoole[$i]->on("receive",function($cli){

});
$swoole[$i]->on("error",function($cli){

});
$swoole[$i]->on("close",function($cli){

});
}



for( $i=0;$i<1000;$i++ ){

foreach( $swoole as $cli ){

$cli->connect("127.0.0.1",9500);

}

}

