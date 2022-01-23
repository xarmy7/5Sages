<h3>Maxence Retier</h3>
<h1>MultiThread</h1> 


## **Description of the project:**
<p> Trying to get started with multiThread by making a scenario with philosophers <br> trying to eat with a number of chines chopsticks so that they cannot eat at the same time.<br></p>

## **How do you run the program properly?**
<p> Before execute the program you need to be in Debug in x64.<br></p>

## **Interface description :**
<p>When you going to launch the program, the console will open and ask the number of wise men <br>around the table. Next, it will be the name of all the philosophers. After, you have just to wait and <br>read what is going on. Have fun ! :)</p>

## **Control:**

 controle      |     signification 
 ------------- | -------------   
 Scape         |   Exit the program

## **What I do in the project ?**
<ol>
    <li>Use mutex to lock some part of the program and avoid data races.</li>
    <li>Use vector of mutex, for the chinese chopsticks and lock when they are not available</li>
    <li>Use random integer functions</li>
    <li>Put some color on specific sentences to make it easier to read the current program.</li> 
</ol>

## **Work in progress**
<p>I started to edit the spawn speed of the sentences</p>

## **Difficulties through the project:**
<p> I had some difficulties throughout the project to understand why we have to use mutex.lock() and <br> and mutex.unlock() and how to use them correctly. </p>

## **References:**

https://learnopengl.com/

https://community.khronos.org/

https://en.cppreference.com/w/

https://stackoverflow.com/