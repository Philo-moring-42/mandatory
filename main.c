// /*       rule        */
// 	0. 최대한 놈에 맞춰서 작성한다.
// 	1. 함수는 하나의 역할만 하게 한다.(그 이상 무조건 분리)
// 	2. 명명시 동사가 먼저 나온다 ex> check_argument()
// 	3. 약어는 최대한 사용하지 않는다.(놈 보다 우선)
// 	4. include가 필요한 소스파일에만 헤더 넣기(리링크 방지, 데이터 절약)
                 
#include "philo.h"
#include <stdio.h>
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_rule	rule;
	t_param	param;

	if (!parsing(argc, argv, &rule))
	{
		printf("FAIL\n");
		return (0);
	}
	if (init_param(&param, &rule) == FAIL)
		return (FAIL);
	if (philo_run(&rule, &param) == FAIL)
		return (0);
		
	// /*             아이디어             */
	// //파싱부                         
	// 	철학자의 수,  굶으면 죽는 시간, 먹는 시간, 자는 시간, (철학자가 최소한 밥을 먹어야 하는 수) -> 구조체 넣는다.
	// 	>> tip. 구조체를 어떻게 할지 많이 이야기 할것.
	// //동작부                           
	// 	초기화(구조체, 초기 값)
	// 	생성(쓰레드)
	// 	선점을 어떻게 할까 (-> 철학자를 최대한 안죽이는 방향으로)
	// 	상호배제 구현 (임계 구간 어떻게 동작 할지)
	// 	출력(어떤 철학자가 포크 잡고, 먹고, 자고, 생각하고 + 죽음) -> 시간이 섞이면 안된다.(시간 순 출력)
	// //체크부	
	// 	죽었는지, 밥 제대로 먹는지 -> 상태를 체크한다. => 어떻게 계속 모니터링을 할까?
	// 	->(메인에서 돌고있는 while (1)내에서 계속 체크한다)
	// 	죽었을 시 프로그램 정상 종료.

}