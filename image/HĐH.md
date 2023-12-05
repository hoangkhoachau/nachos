# Báo Cáo
## 1. Phân công công việc
|STT|MSSV|Họ tên|Công việc được giao|Công việc chưa hoàn thành|Mức độ được|
|---|-----|-------|-----|-----------|-------|
|1|21120434|Bùi Tiến Dũng|J,K,L
|2|21120443|Phạm Thế Duyệt|H,I
|3|21120481|Châu Hoàng Khoa|A,B,C
|4|21120494|Hồ Trọng Lễ|F,G
|5|21120495|Phạm Thị Mỹ Lệ|D,E

 ## 2. Giới thiệu về nachos
 ### 2.1. Tổng quan

 - Nachos là một phần mềm mã nguồn mở (open source) giả lập một máy tính ảo và một số thành phần cơ bản của hệ điều hành chạy trên máy tính ảo này nhằm giúp cho việc tìm hiểu và xây dựng các thành phần phức tạp hơn của hệ điều hành
   - Máy ảo được giả lập có kiến trúc MIPS với hầu hết các thành phần
       và chức năng của một máy thật như: thanh ghi, bộ nhớ, bộ xử lý,
       bộ lệnh, chu kỳ thực thi lệnh, cơ chế ngắt, chu kỳ đồng hồ, …
    - Hệ điều hành Nachos chạy trên máy ảo Nachos là một hệ điều hành đơn chương
       
### 2.2 Giao tiếp giữa HĐH và chương trình người dùng
#### 2.2.1 Mô hình
![x](D:\Document\School\Năm 3\HK1\HĐH\Anh\Anh 2.png)
  - Cũng tương tự như mô hình giao tiếp chung giữa HĐH và chương trình người dùng ở trên, mỗi chương trình trong hệ thống phải có các thông tin cục bộ của nó, bao gồm program counters, registers, stack pointers, và file system handler. Mặc dù user program truy cập các thông tin cục bộ của nó, nhưng HĐH điều khiển các truy cập này, HĐH đảm bảo các yêu cầu từ user program tới kernel không làm cho HĐH sụp đổ. Việc chuyển quyền điều khiển từ user mode thành system mode được thực hiện thông qua system calls, softwave interrupt/trap. Trước khi gọi một lệnh trong hệ thống thì các tham số truyền vào cần thiết phải được nạp vào các thanh ghi của CPU. Để chuyển một biến mang giá trị, tiến trình chỉ việc ghi giá trị vào thanh ghi. Để chuyển một biến tham chiếu, thì giá trị lưu trong thanh ghi được xem như là “user space pointer”. Bởi vì user space pointer không có y nghĩa đối với kernel, mà chúng ta cần là chuyển nội dung từ user space vào kernel sao cho ta có thể xử lý dữ liệu này. Khi trả thông tin từ system về user space, thì các giá trị phải đặt trong các thanh ghi của CPU.
   - Tuy nhiên Nachos là một HĐH nhỏ gọn nhằm mục đích phục vụ cho việc
   tìm hiểu và xây dựng HĐH nên có một số đặc điểm riêng.
   - Các chương trình được viết trên hệ điều hành NachOS được viết trong
   thư mục /code/test.
 - Trước khi chương trình này có thể thực thi được, nó phải được biên
   dịch. Đối với Nachos, tất cả các chương trình trong thư mục
   /code/test/ đều được biên dịch khi biên dịch Nachos, tuy nhiên ta
   hoàn toàn có thể biên dịch các chương trình này mà không cần phải
   biên dịch lại Nachos như sau:

**% …../cross-compiler/decstation-ultrix/bin/gcc -I …../nachos/code/userprog -I…../nachos/code/threads -o ……/test/filename …./test/filename.c**
Quá trình biên dịch chương trình này gồm 3 giai đoạn như sau:
#### 2.2.2 Giao tiếp giữa hệ điều hành và chương trình người dùng



 ### 2.3 Quá trình ngắt và sử lí ngoại lệ
  ## 3. Cài đặt
  ### 3.1 Viết lại file exception.cc
  ### 3.2 Viết lại cấu trúc điều khiển của chương trình
  ### 3.3 
  ### 3.4 Cài đặt system call *int ReadInt()*
  ### 3.5 Cài đặt system call *void PrintInt(int number)*
  ### 3.6 Cài đặt system call *char ReadChar()*
  ### 3.7 Cài đặt system call *void PrintChar(char character)*
  ### 3.8 Cài đặt system call *void ReadString(char[] buffer, int length)*
  ### 3.9 Cài đặt system call *void PrintString(char[] buffer)*
  ### 3.10 Viết chương trình *help*
  ### 3.11 Viết chương trình *ascii*
  ### 3.12 Viết chương trình *sort*
  
  
  
  

