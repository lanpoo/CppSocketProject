### Student ID





### What I have done in the assignment

`In this project, I have achieve all the requirements in this project.I write a number of C++ sicjet programming code.After my test, all of them work normally. And have tge giid yser ubteractuib experience `



### What your code files are and what each one of them does. 

- client.cpp,I complete the client function, responsible for sending my location to the scheduler through TCP.  
- scheduler.cpp.It is responsible for receiving the TCP message of the client, sending its location information to the hospital through UDP, and then deciding which hospital to assign the client to through the information returned by the hospital. Finally, the assignment information is sent to the client and the hospital.It is responsible for receiving the TCP message of the client, sending its location information to the hospital through UDP, and then deciding which hospital to assign the client to through the information returned by the hospital. Finally, the assignment information is sent to the client and the hospital,
- hospitalx.cpp.At the beginning, it will send the initial capacity and occupied capacity to the scheduler, and then wait for the scheduler's scheduling information

### The format of all the messages exchanged.

If there are any errors, there will be a prompt message. If the scheduler sends * to the client, it means that there are no available resources. The hospital will divide the total capacity and the existing capacity by "+".



### Any idiosyncrasy of your project. It should say under what conditions the project fails, if any.

Map information must be named map.txt Otherwise, the project will not run normally



### Reused Code: Did you use code from anywhere for your project? If not, say so. If so, say what functions and where they're from. 

No



