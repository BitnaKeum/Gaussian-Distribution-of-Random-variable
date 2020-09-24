<br>
<h3>Gaussian 분포를 갖는 random variable을 생성하는 프로그램</h4>

Uniform distribution의 random variable X를 변환하여 Gaussian 분포를 갖는 random variable Y를 만들어 낸다.

<br><br>
Random variable X는 난수를 생성하는 rand() 함수를 이용해 생성한다.<br>
random하게 수를 생성하면 그 값들은 대체적으로 uniform distribution을 가지므로 이 난수들이 uniform distribution을 따른다는 전제하에 진행한다. <br>
X를 Y로 변환하는 데에는 ![image](https://user-images.githubusercontent.com/37769713/94163371-ba3ea680-fec2-11ea-88ef-94b07bfc8af2.png) 식이 사용된다.![image](https://user-images.githubusercontent.com/37769713/94163929-641e3300-fec3-11ea-8cde-84dba4cb9e25.png)가 Gaussian function이므로 Gaussian CDF의 역함수를 구한 다음, X를 집어넣으면 된다. 하지만 Gaussian CDF의 역함수 식을 구할 수 없으므로 역함수의 y값은 CDF의 x값이다라는 역함수의 성질을 이용해 우회적으로 구하도록 한다.
<br><br><br><br><br>


![image](https://user-images.githubusercontent.com/37769713/94164055-887a0f80-fec3-11ea-9a98-0fb057bf6411.png)<br>
random_variable의 Histogram
<br><br><br>
![image](https://user-images.githubusercontent.com/37769713/94164198-b4959080-fec3-11ea-846d-14d5724003c0.png)<br>
random_CDF의 Histogram
<br><br><br>
![image](https://user-images.githubusercontent.com/37769713/94164260-c70fca00-fec3-11ea-9625-a3d06a9d0986.png)<br>
평균이 0, 분산이 1^2일 때 Gaussian_random_varaible의 Histogram
<br><br><br>
![image](https://user-images.githubusercontent.com/37769713/94164365-ed356a00-fec3-11ea-8b97-b6e58c561fbd.png)<br>
평균이 0, 분산이 2^2일 때 Gaussian_random_varaible의 Histogram
<br><br><br>
![image](https://user-images.githubusercontent.com/37769713/94164429-fe7e7680-fec3-11ea-8a03-8f6c29de4734.png)<br>
평균이 3, 분산이 2^2일 때 Gaussian_random_varaible의 Histogram
<br><br><br>
![image](https://user-images.githubusercontent.com/37769713/94164474-0b9b6580-fec4-11ea-84c3-237997f8f40a.png)<br>
gaussianCDF의 Histogram
<br><br><br>
![image](https://user-images.githubusercontent.com/37769713/94164594-32f23280-fec4-11ea-96f4-723c20a91445.png)<br>
실제 Gaussian CDF의 Histogram
<br><br><br>



