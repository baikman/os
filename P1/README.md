# P1 – Client Server Sockets  
**CS3310 Operating Systems**

---

## Client-Server Problem

Implement a server application and a corresponding client application on Linux using **C only** (not C++).

This project is designed to give a very basic familiarity with implementing client-server applications in the C programming language on Linux. Begin with reading the website listed in the resources and use the code presented there as a template for the required modifications.

---

## Resources

- [C Socket Tutorial – Echo Server](https://vcansimplify.wordpress.com/2013/03/14/c-socket-tutorial-echo-server/)  
- Example executables can be found on `john: ~dudenho/CS3310/public`

---

## Requirements

1. Modify the port number your client and server use to a unique 5-digit integer (< 65535).  
2. The client must accept its input via **command line arguments** (not from a prompt).  
3. The client must send the input given by the user to the server application.  
4. The server must receive the data from the client.  
5. The server must **transform the data** in some fashion (e.g., switch cases, find the square root, encipher, etc.).  
   - *Have fun with this part.*  
6. The server must send the transformed data as a response to the client.  
7. The client must display the response from the server.  
8. The server must be able to respond to **multiple consecutive client requests** and execute until explicitly quit (^C).  
9. The client should process a single request and then quit on completion.  
10. Usage Example: client "This is a message to be modified."

10. Please adhere to **Cedarville University’s style guide** and comment well.

---

## Turn In

### Electronic Materials:
- All source code files (`.c` & `.h` files) uploaded as individual files  
- A coversheet with:
  - Your name  
  - Class and section  
  - Date  
  - Development environment  
  - Lessons learned  
  - Statement affirming you personally completed the project  
- A **cropped screenshot (.png)** of sample output from your executable(s)