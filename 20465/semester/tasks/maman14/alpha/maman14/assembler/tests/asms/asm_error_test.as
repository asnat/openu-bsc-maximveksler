; test the lable does not start with a number
1ABC: mov r1,r2
1ABCD: .string "Hi"
1ABCDE: .data 12

; Invalid synatx for .string declarations
AA: .string AB"
AA: .string "AB
AA: .string AB
AA: .string a"bce
AA: .string "abc"e
AA: .string abc"e"

; Failure because of empty declarations
.entry
.extern
.string
.data

; Too long assembly line
.data "1234567891234567891234567891234567891234567891234567891234567891234567891"
mov "123456789123456789123456789123456789123456789123456789123456789123456789",r1
