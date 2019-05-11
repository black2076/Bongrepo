# 기능 진도 100% -> 서비스에 반영
# 개발속도는 다름 ex) 뒤에 기능이 앞에 기능보다 먼저 개발될 수 있음
# 단, 앞의 기능과 같이 배포됨.
# 작업 진도가 적힌 정수 배열 progresses
# 개발 속도가 적힌 정수 배열 speeds
# 각 배포마다 몇 개의 기능이 배포되는지 answer

# cond 1 : progresses, speeds 개수 <= 100
# cond 2 : progress < 100, speeds <= 100
# cond 3 : 배포는 하루에 한 번만. ex) 진도95%, 개발속도4% -> 2일 뒤에 배포

# inputoutput ex) [93, 30, 55], [1, 30, 5] -> [2, 1] 배포갯수


def solution(progresses, speeds):
    answer = []

    while len(progresses):
        hndlr = False
        task = 0
        for i in range(len(progresses)):
            progresses[i] += speeds[i]

        while len(progresses) != 0 and progresses[0] >= 100:
            task += 1
            del progresses[0]
            del speeds[0]
            hndlr = True

        if hndlr == True:
            answer.append(task)

    return answer


print(solution([93, 30, 55], [1, 30, 5]))  # 2, 1 // 7 3 9