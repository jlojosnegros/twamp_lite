# twamp_lite

## Compile

  
    mkdir build
    cd build
    cmake .. 
    make twamp_server
    make twamp_client
    
## Execute ( on different terminals) 

    twamp_server ipc///tmp/twamp.ipc
    
    
    twamp_client ipc///tmp/twamp.ipc <seq_number>
    
   
  
