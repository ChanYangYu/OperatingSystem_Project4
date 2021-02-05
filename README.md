# OperatingSystem_Project4
## 개발 목표
- 다중 쓰레드 프로그래밍의 기본 개념을 이해
- lock 및 조건 변수를 사용하는 쓰레드(pthread) 프로그램 구현

## 과제 구현 내용
#### 1. Master-Worker Thread Pool 구현
- 간단한 마스터-워커 쓰레드 풀 구현
- 마스터 쓰레드는 연속적으로 숫자를 생성하여 버퍼에 넣고 워커 쓰레드는 이를 소비 (표준 출력)
- 주어진 코드인 master-worker.c 코드 추가 (코드 완성)
  - % gcc master-worker.c –lpthread (pthread 라이브러리 링크)
  - 4개의 명령어 인자
    - (1) 생성할 숫자 (M)
    - (2) 생성 된 숫자(정수형만) 를 저장할 버퍼 최대 크기 (N)
    - (3) 생성한 숫자(정수형만)를 소비하는 워커 쓰레드 수 (C)
    - (4) 숫자를 생성 할 마스터 쓰레드의 수(P)
#### 2. Reader-Writer Locks 쓰레드 프로그램 구현
- r_lock()과 w_lock()으로 공유 데이터를 처리하여 쓰레드 간 병행성 향상
  - Reader(읽기)이던 Writer(쓰기)이던 쓰레드들이 동시에 데이터를 접근하면 안됨
  - 두 가지 유형의 읽기/쓰기 lock 구현
- 주어진 rw_lock.h에서 read/write lock의 구조를 정의하고 구현
- 주어진 rw_lock-r-test.c와 rw_lock-w-test.c에 각각 읽기/쓰기 쓰레드의 기본 설정으로 read/write
lock 코드 작성
#### 3. pthread를 이용한 사용자 수준 세마포어(SSU_Sem) 구현
- Linux 커널에서 제공하는 세마포어와 충돌되지 않는 사용자 수준 세마포어(SSU_Sem) 구현
  - SSU_Sem의 기능은 리눅스의 세마포어(semaphore)의 기능과 유사
- 주어진 SSU_Sem.h 파일에서 SSU_Sem 구조를 정의
- 주어진 SSU_Sem.c 파일에서 이 구조에서 작동하는 SSU_Sem_init(), SSU_Sem_up() 및
SSU_Sem_down() 구현
