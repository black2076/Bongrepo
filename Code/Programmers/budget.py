# 국가의 예산을 분배
# 국가예산의 총액은 미리 정해짐
# 정해진 총액 이하에서 가능한 한 최대의 총 예산을 배정
# cond 1 : 모든 요청이 배정될 수 있는 경우 = 요청한 금액 그대로 배정
# cond 2 : 모든 요청이 배정될 수 없는 경우 = 상한액 계산
# 그 이상이면 상한액으로 배정
# 그 이하면 예산요청에 대해 요청한 금액 그대로 배정

# ex) 국가예산총액 = 485 // 총예산 M
# 예산요청 - 120, 110, 140, 150 // budgets 배열
# 상한액 - 127 // Upper_limit_amount
# 배정 : 120, 110, 127, 127 // 배정합 = 484 // assignment

# 지방수는 3 ~ 100,000
# 예산요청은 1 ~ 100,000
# 총 예산은 지방수 ~ 1,000,000,000

M = int(input("국가예산총액을 입력해주세요 : "))
budgets_count = int(input("예산요청을 받을 국가 수를 입력해주세요 : "))
budgets = []
for i in range(budgets_count):
    budget = int(input("예산요청금액을 입력해주세요 : "))
    budgets.append(budget)

def solution(budgets, M):
    answer = 0
    assignment = []
    noanswer = "No Assign.."
    Upper_limit_amount = int(input("상한액을 입력해주세요 : "))
    for i in range(len(budgets)):
        if budgets[i] <= Upper_limit_amount:
            assignment.append(budgets[i])
        else:
            assignment.append(Upper_limit_amount)
    if sum(assignment) <= M:
        answer = Upper_limit_amount
        return answer
    else:
        return noanswer

print(solution(budgets, M))


