# 초 단위로 기록된 주식가격 배열 prices
# 가격이 떨어지지 않은 기간 = 몇 초(seconds)
# cond 1 : prices value 1 ~ 10,000
# cond 2 : prices length 2 ~ 100,000

# input, output ex) [1,2,3,2,3] -> [4,3,1,1,0]

# 3초 / 3원 -> 1초뒤에 떨어짐 / 1초간 가격이 떨어지지 않음 = return 1
def solution(prices):
    instock = prices
    answer = []
    # print(answer)
    for i in range(len(instock)):
        for j in range(i+1, len(instock)):
            if instock[i] <= instock[j]:
                if j == (len(instock)-1):
                    answer.insert(i, j-i)
            else:
                answer.insert(i, j-i)
                break
        if i+1 == len(instock):
            answer.insert(i+1, 0)

    return answer


stock_price = [1, 2, 3, 2, 3]
print(solution(stock_price))
