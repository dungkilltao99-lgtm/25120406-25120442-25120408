Tên môn: Cấu trúc dữ liệu và giải thuật
Thời gian học: T2(6-7.5)
Họ tên sinh viên: Lê Hồ Quốc Thịnh - 25120442
                  Cao Bá Nhựt - 25120406
                  Nguyễn Tiến Phát - 25120408
A. Integer Sort

Thuật toán tốt nhất ở lần chạy đầu tiên: 

Thuật toán được lựa chọn để giải quyết bài toán sắp xếp mảng số nguyên là Radix Sort (Sắp xếp theo cơ số) kết hợp với Counting Sort (Sắp xếp đếm), được triển khai theo hướng từ bit thấp đến bit cao (LSD - Least Significant Digit).
Thay vì sử dụng hệ cơ số 10 hoặc cơ số 256 thông thường, thuật toán xử lý dữ liệu ở cơ số 65536 (tương đương 2^16). Mỗi số nguyên 32-bit sẽ được tách thành 2 cụm 16-bit. Nhờ đó, thuật toán chỉ cần thực hiện đúng 2 vòng quét (passes) để sắp xếp toàn bộ mảng dữ liệu.
Để xử lý các số nguyên âm, thuật toán thực hiện phép lật bit dấu (bit cao nhất) của mọi phần tử trước khi sắp xếp. Bước này giúp tịnh tiến toàn bộ tập giá trị sang miền số không dấu, cho phép Radix Sort xử lý mượt mà như số nguyên dương. Sau khi mảng đã được sắp xếp, thuật toán tiến hành lật lại bit dấu một lần nữa để trả các số về giá trị thực tế ban đầu.

Các phương thức tối ưu hóa liên quan:

Mã nguồn áp dụng các kỹ thuật tối ưu hóa chuyên sâu ở mức phần cứng (Hardware-level Optimization) để ép thời gian chạy xuống mức thấp nhất:
Tối ưu hóa Nhập/Xuất (Fast I/O): Thay vì sử dụng các luồng I/O tiêu chuẩn chậm chạp như std::cin/std::cout hay scanf/printf, chương trình cấp phát một mảng đệm (buffer) có kích thước 1MB và sử dụng hàm fread/fwrite để đọc/ghi trực tiếp toàn bộ khối dữ liệu từ bộ nhớ. Quá trình phân tích cú pháp từ ký tự ASCII sang số nguyên được tự cài đặt thủ công.
Tối ưu hóa bằng Toán tử Bitwise: Mọi phép tính toán chia lấy dư và chia nguyên đều được thay thế bằng toán tử bit. Phép lấy phần dư được thay bằng phép AND (& 0xFFFF), phép chia cơ số được thay bằng phép dịch phải (>> 16), và thao tác lật bit dấu được thực thi bằng phép XOR (^ 0x80000000). Các phép toán bitwise được CPU xử lý chỉ trong 1 chu kỳ xung nhịp, nhanh hơn đáng kể so với phép toán số học.
Tối ưu hóa vòng quét (Pass Reduction): Việc lựa chọn cơ số 65536 là một sự đánh đổi có chủ ý. Kích thước mảng đếm tăng lên nhưng bù lại giảm một nửa số vòng lặp sắp xếp trên mảng dữ liệu chính (từ 4 vòng xuống 2 vòng).

Lý giải tại sao phương pháp này tốt nhất:

So với các thuật toán sắp xếp dựa trên so sánh phổ biến ở lần cài đặt đầu tiên, cách tiếp cận này là toàn diện và tối ưu nhất vì những lý do sau:
Độ phức tạp tiệm cận tuyến tính O(N): Giới hạn tốc độ của các thuật toán so sánh tốt nhất hiện nay (như IntroSort dùng trong std::sort) là O(N log N). Với bộ dữ liệu 100.000 phần tử, thuật toán so sánh cần hàng triệu thao tác. Trong khi đó, Radix Sort cơ sở 65536 hoạt động với độ phức tạp O(d * N) (với d = 2), biến thời gian chạy thực tế trở thành đồ thị tuyến tính O(N) với hệ số hằng số cực kỳ nhỏ.
Thân thiện với bộ nhớ đệm (Cache Locality): Mảng đếm count1 và count2 có kích thước 65536 phần tử (tương đương khoảng 256KB). Kích thước này vừa vặn hoàn toàn nằm gọn bên trong bộ nhớ đệm tốc độ cao L2/L3 Cache của các CPU hiện đại, triệt tiêu tối đa hiện tượng trễ bộ nhớ (Cache Miss).
Tối ưu hóa luồng lệnh CPU (Branch Prediction Friendly): Thuật toán Quicksort đòi hỏi rất nhiều lệnh rẽ nhánh (if) để chia để trị, dễ dẫn đến hiện tượng CPU dự đoán sai nhánh (Branch Misprediction) và phải xóa bỏ luồng lệnh (pipeline flush). Radix Sort trong bài cài đặt hoàn toàn không có bất kỳ lệnh rẽ nhánh nào bên trong các vòng lặp cốt lõi, giúp CPU hoạt động xuyên suốt với công suất tối đa.
Loại bỏ nút thắt cổ chai I/O: Trong các bài toán cấu trúc dữ liệu với lượng Input lớn, thời gian đọc/ghi thường chiếm từ 50% - 80% tổng thời gian thực thi. Fast I/O giúp loại bỏ hoàn toàn độ trễ đồng bộ (synchronization) của C++, đảm bảo chương trình chỉ thực sự tiêu tốn thời gian cho việc tính toán lõi.

B. Lexicographic Sort

Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên:

Thuật toán được sử dụng để giải quyết bài toán sắp xếp chuỗi theo thứ tự từ điển là MSD (Most Significant Digit) Radix Sort kết hợp với Insertion Sort (Sắp xếp chèn) tạo thành một mô hình lai (Hybrid Sort).
Thay vì sắp xếp toàn bộ chuỗi cùng lúc, MSD Radix Sort xử lý các chuỗi theo từng ký tự từ trái sang phải (bắt đầu từ vị trí d = 0). Thuật toán sử dụng kỹ thuật phân lô (bucket/counting) dựa trên giá trị ASCII của ký tự hiện tại để chia mảng ban đầu thành 256 nhóm nhỏ hơn. Sau khi phân nhóm xong, thuật toán tiếp tục gọi đệ quy để phân tách từng nhóm đó dựa trên ký tự tiếp theo (d + 1). Quá trình này lặp lại cho đến khi toàn bộ mảng được sắp xếp hoàn toàn.

Các phương thức tối ưu hóa liên quan:

Mã nguồn áp dụng các kỹ thuật tối ưu hóa cực kỳ sâu sát về mặt quản lý bộ nhớ và điều hướng luồng thực thi:
Quản lý bộ nhớ phẳng (Memory Pool) & Con trỏ chuỗi: Chương trình loại bỏ hoàn toàn việc sử dụng đối tượng std::string hay cấp phát động mảng hai chiều. Thay vào đó, toàn bộ dữ liệu đầu vào được lưu liền mạch trên một bộ đệm (pool) khổng lồ cấp phát 1 lần (char* pool = new char[IN_BUF_SIZE]). Các chuỗi được đại diện bởi một cấu trúc thu gọn StringRef chỉ chứa đúng một con trỏ trỏ đến vị trí chuỗi trong pool. Quá trình hoán vị khi sắp xếp thực chất chỉ là hoán vị các con trỏ nhẹ (8 bytes), không hề sao chép dữ liệu chuỗi.
Tối ưu hóa ngưỡng đệ quy (Recursive Thresholding): Đây là kỹ thuật cốt lõi giúp MSD Radix Sort không bị thoái hóa. Khi gọi đệ quy phân nhỏ mảng, nếu kích thước nhóm (bucket size) nhỏ hơn 16 phần tử (n < 16), thuật toán lập tức ngắt đệ quy và chuyển sang dùng Insertion Sort kết hợp strcmp.
Fast I/O Buffer lớn: Sử dụng bộ đệm lên đến 16MB (1 << 24) cho cả đầu vào và đầu ra thông qua fread và fwrite, giúp nạp gần như toàn bộ test case vào RAM trong một lần duy nhất. Ký tự null (\0) được chèn thủ công vào cuối mỗi chuỗi ngay trong lúc parse dữ liệu.
Cắt tỉa nhánh đệ quy (Branch Pruning): Vòng lặp đệ quy (for (int i = 1; i < 256; i++)) cố tình bắt đầu từ index 1 để bỏ qua bucket 0 (chứa ký tự kết thúc chuỗi \0). Nghĩa là các chuỗi đã duyệt hết độ dài sẽ không bị đưa vào tầng đệ quy sâu hơn.

Lý giải tại sao phương pháp này tốt nhất:

Cách cài đặt này hoàn toàn vượt trội so với các thuật toán dựa trên so sánh (như QuickSort dùng mảng std::string trong STL) vì những lý do then chốt sau:
Độ phức tạp tuyến tính theo tổng độ dài: Thuật toán std::sort sử dụng cơ chế chia để trị, với độ phức tạp O(Nlog N X L) (với L là độ dài trung bình của chuỗi, do mỗi lần so sánh if (a < b) đều phải duyệt lại chuỗi từ đầu). Ngược lại, MSD Radix Sort có thời gian chạy tỷ lệ thuận với tổng số lượng ký tự của tất cả các chuỗi O(W) (với W là tổng độ dài). Mỗi ký tự trên mỗi chuỗi chỉ được xét qua đúng 1 lần duy nhất ở mỗi tầng đệ quy, không có sự so sánh dư thừa.
Triệt tiêu chi phí Overhead của đệ quy: MSD Radix Sort thuần túy rất dễ bị chậm do phải cấp phát mảng đếm (count array) và gọi hàm đệ quy hàng ngàn lần cho những mảng con chỉ có vài phần tử. Việc áp dụng Insertion Sort cho các mảng có N < 16 giúp giải quyết triệt để vấn đề này, vì Insertion Sort chạy cực nhanh trên dữ liệu nhỏ, giúp giảm tới 80-90% số lượng các lời gọi đệ quy không cần thiết dưới đáy cây thực thi.
Thân thiện tuyệt đối với bộ nhớ Cache (Cache Line Optimization): Việc lưu trữ tất cả các chuỗi nối tiếp nhau trong một pool duy nhất giúp CPU nạp dữ liệu một cách tuần tự và liền mạch vào Cache L1/L2. Điều này giải quyết được điểm yếu "tử huyệt" của cấu trúc mảng (array of arrays) hoặc mảng con trỏ thông thường, nơi mà dữ liệu bị phân mảnh rải rác khắp nơi trên RAM gây ra tình trạng Cache Miss liên tục.

C. Length-aware Lexicographic String Sort

Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên:

Thuật toán được lựa chọn là một hệ thống phân loại hai giai đoạn (Two-stage Sorting System), kết hợp giữa Counting Sort (Sắp xếp đếm) để xử lý chiều dài và MSD Radix Sort (lai với Insertion Sort) để xử lý thứ tự từ điển.
Giai đoạn 1 (Phân nhóm theo độ dài): Thuật toán tính toán độ dài của từng chuỗi ngay trong lúc đọc dữ liệu đầu vào. Sau đó, sử dụng Counting Sort để gom nhóm tất cả các chuỗi có cùng độ dài lại với nhau vào mảng sorted_by_len. Bước này phân tách bài toán lớn thành các bài toán nhỏ độc lập, trong đó mỗi nhóm chỉ chứa các chuỗi có chiều dài bằng nhau.
Giai đoạn 2 (Sắp xếp từ điển nội bộ): Đối với mỗi nhóm chuỗi có cùng độ dài (nếu nhóm có nhiều hơn 1 phần tử), thuật toán áp dụng tiếp MSD Radix Sort. Do các chuỗi trong cùng một nhóm đã biết trước độ dài cố định (max_len), thuật toán phân lô dựa trên từng ký tự từ trái sang phải. Khi kích thước lô giảm xuống dưới 25 phần tử, hệ thống tự động chuyển sang Insertion Sort để hoàn tất việc sắp xếp.

Các phương thức tối ưu hóa liên quan: 

Mã nguồn áp dụng chiến lược cấp phát tĩnh và quản lý bộ nhớ không sao chép (Zero-copy), triệt tiêu tối đa các thao tác thừa:
Zero-copy Parsing & Cached Length: Thay vì đọc từng chuỗi và gọi strlen(), chương trình đọc toàn bộ đầu vào vào một bộ đệm khổng lồ (in_buf kích thước 16MB) chỉ bằng một lệnh fread. Con trỏ của mỗi chuỗi (StringRef.s) được trỏ thẳng vào vị trí tương ứng trong in_buf, đồng thời ký tự khoảng trắng/xuống dòng được ghi đè thủ công thành \0. Độ dài chuỗi được tính toán qua phép trừ con trỏ và lưu sẵn vào cấu trúc StringRef.len. Toàn bộ quá trình nạp dữ liệu diễn ra mà không có bất kỳ thao tác sao chép chuỗi (copy) hay cấp phát động (new string) nào.
Tối ưu hóa In-place MSD Radix Sort: Hàm msd_sort_fixed_len được truyền vào tham số max_len. Nhờ biết trước độ dài nhóm hiện tại, vòng lặp đệ quy ngắt ngay lập tức khi d >= max_len mà không cần gọi các hàm kiểm tra độ dài chuỗi dư thừa, tiết kiệm một lượng lớn chu kỳ xung nhịp (clock cycles) của CPU.
Ngưỡng đệ quy tối ưu hóa (Thresholding): Tương tự bài B, việc áp dụng Insertion Sort khi kích thước nhóm n < 25 giúp loại bỏ hoàn toàn chi phí gọi hàm đệ quy và cấp phát mảng đếm (count array) cho các tập dữ liệu nhỏ ở đáy cây đệ quy.
Batch Memory Output: Quá trình in kết quả không ghi từng ký tự mà dùng memcpy để chép toàn bộ chuỗi vào bộ đệm đầu ra (out_buf). Khi bộ đệm gần đầy, hệ thống mới xả (flush) một lần bằng fwrite.

Lý giải tại sao phương pháp này tốt nhất: 

Cách tiếp cận chia để trị theo hai giai đoạn này là giải pháp toàn diện và tối ưu nhất cho biến thể bài toán (sắp xếp theo độ dài trước, từ điển sau) vì những lý do sau:
Loại bỏ chi phí so sánh độ dài đa luồng: Nếu sử dụng hàm std::sort với một hàm cmp tùy chỉnh (so sánh độ dài trước, nếu bằng nhau thì so sánh chuỗi), CPU sẽ phải thực hiện phép kiểm tra độ dài if (a.len != b.len) lặp đi lặp lại hàng triệu lần trong suốt quá trình phân nhánh của QuickSort. Bằng cách sử dụng Counting Sort (với độ phức tạp O(N)) để phân tách độ dài ngay từ đầu, giai đoạn sắp xếp chuỗi sau đó hoàn toàn không còn gánh nặng phải kiểm tra chiều dài.
Độ phức tạp thời gian O(N + W): Thuật toán sở hữu thời gian thực thi tiệm cận tuyến tính. Counting Sort mất O(N) thời gian, và MSD Radix Sort duyệt qua các ký tự với chi phí tỷ lệ thuận với tổng số lượng ký tự O(W). Không có sự so sánh lặp lại nào xảy ra như trong các thuật toán so sánh O(N log N).
Tối đa hóa Cache L1/L2 (Cache-friendliness): Việc định tuyến tất cả con trỏ chuỗi trực tiếp trên mảng một chiều in_buf đảm bảo dữ liệu nằm liên tiếp nhau trên RAM. Khi thuật toán Radix Sort hoặc Insertion Sort truy xuất ký tự để sắp xếp, CPU có thể nạp các khối bộ nhớ vào Cache một cách tuần tự (spatial locality), giảm thiểu triệt để hiện tượng trễ bộ nhớ (Memory Bottleneck).
An toàn về bộ nhớ: Cấu trúc StringRef chỉ chứa một con trỏ 8-byte và một số nguyên 4-byte. Việc hoán vị trong lúc sắp xếp thực chất chỉ tốn 12 byte bộ nhớ, đảm bảo tốc độ cực cao bất kể độ dài thực tế của chuỗi là 10 hay 100 ký tự.
