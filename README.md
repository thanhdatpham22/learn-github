# PROJECT CAR DASHBOARD 

## Giới Thiệu Project
Project "Car Dashboard" là một hệ thống mô phỏng giao diện điều khiển cho xe ô tô, tập trung vào các chức năng quản lý vận tốc, điều chỉnh chế độ lái, giám sát tiêu hao năng lượng, và đảm bảo an toàn. Hệ thống sử dụng dữ liệu từ file CSV để cập nhật thông tin thời gian thực, giúp người dùng theo dõi tình trạng xe và thực hiện các điều chỉnh cần thiết.

## Mục tiêu của Project
- Hiển thị Thông Số Vận Hành: Cung cấp thông tin về tốc độ xe, mức pin, điều hòa và quãng đường còn lại.
- Quản lý Chế Độ Lái: Cho phép lựa chọn chế độ lái SPORT hoặc ECO, mỗi chế độ sẽ có đặc điểm vận hành riêng.
- Tính Toán Tiêu Hao Năng Lượng: Dự đoán mức tiêu hao năng lượng dựa trên vận tốc, điều hòa, và mức gió.
- Đảm Bảo An Toàn: Quản lý các yếu tố an toàn, như ngăn việc đạp ga và phanh cùng lúc.

## Kỹ Thuật Sử Dụng trong Project
- Design Patterns: Project sử dụng mẫu thiết kế Observer để tổ chức mã nguồn hiệu quả.
- Đa Luồng (Multithreading): Các thread riêng biệt xử lý dữ liệu từ file CSV và đầu vào từ người dùng.
- Bảo vệ Dữ Liệu (Mutex): Sử dụng cơ chế khóa (mutex) để đảm bảo dữ liệu không bị xung đột khi nhiều thread truy cập.

## Cấu trúc thư mục
![image](https://github.com/user-attachments/assets/1f2249c4-8568-44e5-9073-58bd2a5a05f1)

## Chi tiết các thành phần
### Main
- Khởi tạo các đối tượng chính của hệ thống bao gồm: 
    - DashboardController
    - DisplayManager
    - SpeedCalculator
    - BatteryManager
    - DriveModeManager
    - SafetyManager
- Tạo các thread để hiển thị các dữ liệu mới nhất lên màn hình console:
    - Thread 1: Đọc dữ liệu từ file Database.csv sau mỗi 1s và cập nhật vào DashboardController.
    - Thread 2: Xử lý các lệnh điều khiển từ người dùng (bàn phím) như thay đổi chế độ lái, bật/tắt điều hòa, nhấn ga/phanh.
    - Thread chính: Điều phối các hoạt động trong hệ thống, liên tục cập nhật giao diện và điều chỉnh các thành phần liên quan.
### DashboardController
Là thành phần trung tâm trong project "Car Dashboard", chịu trách nhiệm quản lý và điều phối dữ liệu từ các thành phần khác, đồng thời thông báo cho các thành phần liên quan khi có thay đổi dữ liệu. Với việc sử dụng Observer Pattern, DashboardController có thể dễ dàng thông báo cho các thành phần hiển thị hoặc xử lý khác mỗi khi có cập nhật dữ liệu mới từ file CSV.
### DisplayManager
Quản lý việc hiển thị dữ liệu lên giao diện. Nó lắng nghe các cập nhật từ DashboardController và sử dụng các thông số mới nhất (vận tốc, mức pin, nhiệt độ điều hòa,...) để cập nhật giao diện một cách chính xác. DisplayManager đóng vai trò là một observer của DashboardController, tự động cập nhật thông tin mỗi khi có thay đổi từ dữ liệu trung tâm. 
### SpeedCalculator
Chịu trách nhiệm tính toán và điều chỉnh vận tốc của xe dựa trên các yếu tố đầu vào như ga, phanh, và chế độ lái. Nó xác định vận tốc tối đa theo chế độ lái hiện tại (SPORT hoặc ECO) và điều chỉnh vận tốc để đảm bảo phù hợp với các điều kiện vận hành của xe.
### BatteryManager
Chịu trách nhiệm quản lý mức tiêu hao năng lượng của pin trong quá trình vận hành xe bao gồm tính toán mức tiêu hao pin dựa trên các yếu tố như vận tốc, điều hòa, và mức gió, đồng thời dự đoán quãng đường còn lại có thể di chuyển dựa trên mức pin hiện tại. Nó đảm bảo người lái có thể theo dõi tình trạng năng lượng của xe và có dự báo chính xác về quãng đường còn lại.
### DriveModeManager
Chịu trách nhiệm quản lý các chế độ lái của xe, như SPORT và ECO. Mỗi chế độ lái được thiết kế để đáp ứng nhu cầu vận hành khác nhau: SPORT ưu tiên hiệu suất với công suất cao và khả năng tăng tốc mạnh, trong khi ECO tập trung vào tiết kiệm năng lượng với giới hạn tốc độ và công suất thấp hơn. DriveModeManager điều chỉnh các tham số vận hành để tối ưu hóa hiệu suất hoặc tiết kiệm năng lượng tùy thuộc vào chế độ lái hiện tại.
### SafetyManager
Chịu trách nhiệm đảm bảo an toàn khi điều khiển xe, đặc biệt trong các trường hợp người lái có thể thực hiện các thao tác nguy hiểm, kiểm soát các yếu tố an toàn như ngăn việc đạp ga và phanh cùng lúc, giảm tốc độ khi phanh, và cho phép xe di chuyển tiếp khi phanh được giải phóng.

## Sử dụng makefile để build project
- Dùng lệnh `make` để build và run chương trình, các file object (.o) và file thực thi (.exe) sẽ nằm ở trong thư mục `bin`
- Dùng lệnh `make clean` để xóa các file oject (.o) và file thực thi (.exe)
