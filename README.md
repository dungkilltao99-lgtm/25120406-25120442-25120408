# Tên môn: Cấu trúc dữ liệu và giải thuật

# Thời gian học: HK2 2025-2026

# Họ tên sinh viên: 

- Lê Hồ Quốc Thịnh - 25120442

- Cao Bá Nhựt - 25120406

- Nguyễn Tiến Phát - 25120408

### I. Thuật toán chạy tốt nhất ở lần đầu tiên:

## A. Integer Sort

# 1. Thuật toán:

- Thuật toán được lựa chọn để giải quyết bài toán sắp xếp mảng số nguyên là Radix Sort (Sắp xếp theo cơ số) kết hợp với Counting Sort (Sắp xếp đếm), được triển khai theo hướng từ bit thấp đến bit cao (LSD - Least Significant Digit).
- Thay vì sử dụng hệ cơ số 10 hoặc cơ số 256 thông thường, thuật toán xử lý dữ liệu ở cơ số 65536 (tương đương 2^16). Mỗi số nguyên 32-bit sẽ được tách thành 2 cụm 16-bit. Nhờ đó, thuật toán chỉ cần thực hiện đúng 2 vòng quét (passes) để sắp xếp toàn bộ mảng dữ liệu.
- Để xử lý các số nguyên âm, thuật toán thực hiện phép lật bit dấu (bit cao nhất) của mọi phần tử trước khi sắp xếp. Bước này giúp tịnh tiến toàn bộ tập giá trị sang miền số không dấu, cho phép Radix Sort xử lý mượt mà như số nguyên dương. Sau khi mảng đã được sắp xếp, thuật toán tiến hành lật lại bit dấu một lần nữa để trả các số về giá trị thực tế ban đầu.

# 2. Các phương thức tối ưu hóa liên quan:

Mã nguồn áp dụng các kỹ thuật tối ưu hóa chuyên sâu ở mức phần cứng (Hardware-level Optimization) để ép thời gian chạy xuống mức thấp nhất:
- Tối ưu hóa Nhập/Xuất (Fast I/O): Thay vì sử dụng các luồng I/O tiêu chuẩn chậm chạp như std::cin/std::cout hay scanf/printf, chương trình cấp phát một mảng đệm (buffer) có kích thước 1MB và sử dụng hàm fread/fwrite để đọc/ghi trực tiếp toàn bộ khối dữ liệu từ bộ nhớ. Quá trình phân tích cú pháp từ ký tự ASCII sang số nguyên được tự cài đặt thủ công.
- Tối ưu hóa bằng Toán tử Bitwise: Mọi phép tính toán chia lấy dư và chia nguyên đều được thay thế bằng toán tử bit. Phép lấy phần dư được thay bằng phép AND (& 0xFFFF), phép chia cơ số được thay bằng phép dịch phải (>> 16), và thao tác lật bit dấu được thực thi bằng phép XOR (^ 0x80000000). Các phép toán bitwise được CPU xử lý chỉ trong 1 chu kỳ xung nhịp, nhanh hơn đáng kể so với phép toán số học.
- Tối ưu hóa vòng quét (Pass Reduction): Việc lựa chọn cơ số 65536 là một sự đánh đổi có chủ ý. Kích thước mảng đếm tăng lên nhưng bù lại giảm một nửa số vòng lặp sắp xếp trên mảng dữ liệu chính (từ 4 vòng xuống 2 vòng).

# 3. Lý giải tại sao phương pháp này tốt nhất:

So với các thuật toán sắp xếp dựa trên so sánh phổ biến ở lần cài đặt đầu tiên, cách tiếp cận này là toàn diện và tối ưu nhất vì những lý do sau:
- Độ phức tạp tiệm cận tuyến tính O(N): Giới hạn tốc độ của các thuật toán so sánh tốt nhất hiện nay (như IntroSort dùng trong std::sort) là O(N log N). Với bộ dữ liệu 100.000 phần tử, thuật toán so sánh cần hàng triệu thao tác. Trong khi đó, Radix Sort cơ sở 65536 hoạt động với độ phức tạp O(d * N) (với d = 2), biến thời gian chạy thực tế trở thành đồ thị tuyến tính O(N) với hệ số hằng số cực kỳ nhỏ.
- Thân thiện với bộ nhớ đệm (Cache Locality): Mảng đếm count1 và count2 có kích thước 65536 phần tử (tương đương khoảng 256KB). Kích thước này vừa vặn hoàn toàn nằm gọn bên trong bộ nhớ đệm tốc độ cao L2/L3 Cache của các CPU hiện đại, triệt tiêu tối đa hiện tượng trễ bộ nhớ (Cache Miss).
- Tối ưu hóa luồng lệnh CPU (Branch Prediction Friendly): Thuật toán Quicksort đòi hỏi rất nhiều lệnh rẽ nhánh (if) để chia để trị, dễ dẫn đến hiện tượng CPU dự đoán sai nhánh (Branch Misprediction) và phải xóa bỏ luồng lệnh (pipeline flush). Radix Sort trong bài cài đặt hoàn toàn không có bất kỳ lệnh rẽ nhánh nào bên trong các vòng lặp cốt lõi, giúp CPU hoạt động xuyên suốt với công suất tối đa.
- Loại bỏ nút thắt cổ chai I/O: Trong các bài toán cấu trúc dữ liệu với lượng Input lớn, thời gian đọc/ghi thường chiếm từ 50% - 80% tổng thời gian thực thi. Fast I/O giúp loại bỏ hoàn toàn độ trễ đồng bộ (synchronization) của C++, đảm bảo chương trình chỉ thực sự tiêu tốn thời gian cho việc tính toán lõi.

## B. Lexicographic Sort

# 1. Thuật toán:

- Thuật toán được sử dụng để giải quyết bài toán sắp xếp chuỗi theo thứ tự từ điển là MSD (Most Significant Digit) Radix Sort kết hợp với Insertion Sort (Sắp xếp chèn) tạo thành một mô hình lai (Hybrid Sort).
Thay vì sắp xếp toàn bộ chuỗi cùng lúc, MSD Radix Sort xử lý các chuỗi theo từng ký tự từ trái sang phải (bắt đầu từ vị trí d = 0). Thuật toán sử dụng kỹ thuật phân lô (bucket/counting) dựa trên giá trị ASCII của ký tự hiện tại để chia mảng ban đầu thành 256 nhóm nhỏ hơn. Sau khi phân nhóm xong, thuật toán tiếp tục gọi đệ quy để phân tách từng nhóm đó dựa trên ký tự tiếp theo (d + 1). Quá trình này lặp lại cho đến khi toàn bộ mảng được sắp xếp hoàn toàn.

# 2. Các phương thức tối ưu hóa liên quan:

Mã nguồn áp dụng các kỹ thuật tối ưu hóa cực kỳ sâu sát về mặt quản lý bộ nhớ và điều hướng luồng thực thi:
- Quản lý bộ nhớ phẳng (Memory Pool) & Con trỏ chuỗi: Chương trình loại bỏ hoàn toàn việc sử dụng đối tượng std::string hay cấp phát động mảng hai chiều. Thay vào đó, toàn bộ dữ liệu đầu vào được lưu liền mạch trên một bộ đệm (pool) khổng lồ cấp phát 1 lần (char* pool = new char[IN_BUF_SIZE]). Các chuỗi được đại diện bởi một cấu trúc thu gọn StringRef chỉ chứa đúng một con trỏ trỏ đến vị trí chuỗi trong pool. Quá trình hoán vị khi sắp xếp thực chất chỉ là hoán vị các con trỏ nhẹ (8 bytes), không hề sao chép dữ liệu chuỗi.
- Tối ưu hóa ngưỡng đệ quy (Recursive Thresholding): Đây là kỹ thuật cốt lõi giúp MSD Radix Sort không bị thoái hóa. Khi gọi đệ quy phân nhỏ mảng, nếu kích thước nhóm (bucket size) nhỏ hơn 16 phần tử (n < 16), thuật toán lập tức ngắt đệ quy và chuyển sang dùng Insertion Sort kết hợp strcmp.
- Fast I/O Buffer lớn: Sử dụng bộ đệm lên đến 16MB (1 << 24) cho cả đầu vào và đầu ra thông qua fread và fwrite, giúp nạp gần như toàn bộ test case vào RAM trong một lần duy nhất. Ký tự null (\0) được chèn thủ công vào cuối mỗi chuỗi ngay trong lúc parse dữ liệu.
- Cắt tỉa nhánh đệ quy (Branch Pruning): Vòng lặp đệ quy (for (int i = 1; i < 256; i++)) cố tình bắt đầu từ index 1 để bỏ qua bucket 0 (chứa ký tự kết thúc chuỗi \0). Nghĩa là các chuỗi đã duyệt hết độ dài sẽ không bị đưa vào tầng đệ quy sâu hơn.

# 3. Lý giải tại sao phương pháp này tốt nhất:

Cách cài đặt này hoàn toàn vượt trội so với các thuật toán dựa trên so sánh (như QuickSort dùng mảng std::string trong STL) vì những lý do then chốt sau:
- Độ phức tạp tuyến tính theo tổng độ dài: Thuật toán std::sort sử dụng cơ chế chia để trị, với độ phức tạp O(Nlog N X L) (với L là độ dài trung bình của chuỗi, do mỗi lần so sánh if (a < b) đều phải duyệt lại chuỗi từ đầu). Ngược lại, MSD Radix Sort có thời gian chạy tỷ lệ thuận với tổng số lượng ký tự của tất cả các chuỗi O(W) (với W là tổng độ dài). Mỗi ký tự trên mỗi chuỗi chỉ được xét qua đúng 1 lần duy nhất ở mỗi tầng đệ quy, không có sự so sánh dư thừa.
- Triệt tiêu chi phí Overhead của đệ quy: MSD Radix Sort thuần túy rất dễ bị chậm do phải cấp phát mảng đếm (count array) và gọi hàm đệ quy hàng ngàn lần cho những mảng con chỉ có vài phần tử. Việc áp dụng Insertion Sort cho các mảng có N < 16 giúp giải quyết triệt để vấn đề này, vì Insertion Sort chạy cực nhanh trên dữ liệu nhỏ, giúp giảm tới 80-90% số lượng các lời gọi đệ quy không cần thiết dưới đáy cây thực thi.
- Thân thiện tuyệt đối với bộ nhớ Cache (Cache Line Optimization): Việc lưu trữ tất cả các chuỗi nối tiếp nhau trong một pool duy nhất giúp CPU nạp dữ liệu một cách tuần tự và liền mạch vào Cache L1/L2. Điều này giải quyết được điểm yếu "tử huyệt" của cấu trúc mảng (array of arrays) hoặc mảng con trỏ thông thường, nơi mà dữ liệu bị phân mảnh rải rác khắp nơi trên RAM gây ra tình trạng Cache Miss liên tục.

## C. Length-aware Lexicographic String Sort

# 1. Thuật toán:

- Thuật toán được lựa chọn là một hệ thống phân loại hai giai đoạn (Two-stage Sorting System), kết hợp giữa Counting Sort (Sắp xếp đếm) để xử lý chiều dài và MSD Radix Sort (lai với Insertion Sort) để xử lý thứ tự từ điển.
- Giai đoạn 1 (Phân nhóm theo độ dài): Thuật toán tính toán độ dài của từng chuỗi ngay trong lúc đọc dữ liệu đầu vào. Sau đó, sử dụng Counting Sort để gom nhóm tất cả các chuỗi có cùng độ dài lại với nhau vào mảng sorted_by_len. Bước này phân tách bài toán lớn thành các bài toán nhỏ độc lập, trong đó mỗi nhóm chỉ chứa các chuỗi có chiều dài bằng nhau.
- Giai đoạn 2 (Sắp xếp từ điển nội bộ): Đối với mỗi nhóm chuỗi có cùng độ dài (nếu nhóm có nhiều hơn 1 phần tử), thuật toán áp dụng tiếp MSD Radix Sort. Do các chuỗi trong cùng một nhóm đã biết trước độ dài cố định (max_len), thuật toán phân lô dựa trên từng ký tự từ trái sang phải. Khi kích thước lô giảm xuống dưới 25 phần tử, hệ thống tự động chuyển sang Insertion Sort để hoàn tất việc sắp xếp.

# 2. Các phương thức tối ưu hóa liên quan: 

Mã nguồn áp dụng chiến lược cấp phát tĩnh và quản lý bộ nhớ không sao chép (Zero-copy), triệt tiêu tối đa các thao tác thừa:
- Zero-copy Parsing & Cached Length: Thay vì đọc từng chuỗi và gọi strlen(), chương trình đọc toàn bộ đầu vào vào một bộ đệm khổng lồ (in_buf kích thước 16MB) chỉ bằng một lệnh fread. Con trỏ của mỗi chuỗi (StringRef.s) được trỏ thẳng vào vị trí tương ứng trong in_buf, đồng thời ký tự khoảng trắng/xuống dòng được ghi đè thủ công thành \0. Độ dài chuỗi được tính toán qua phép trừ con trỏ và lưu sẵn vào cấu trúc StringRef.len. Toàn bộ quá trình nạp dữ liệu diễn ra mà không có bất kỳ thao tác sao chép chuỗi (copy) hay cấp phát động (new string) nào.
- Tối ưu hóa In-place MSD Radix Sort: Hàm msd_sort_fixed_len được truyền vào tham số max_len. Nhờ biết trước độ dài nhóm hiện tại, vòng lặp đệ quy ngắt ngay lập tức khi d >= max_len mà không cần gọi các hàm kiểm tra độ dài chuỗi dư thừa, tiết kiệm một lượng lớn chu kỳ xung nhịp (clock cycles) của CPU.
- Ngưỡng đệ quy tối ưu hóa (Thresholding): Tương tự bài B, việc áp dụng Insertion Sort khi kích thước nhóm n < 25 giúp loại bỏ hoàn toàn chi phí gọi hàm đệ quy và cấp phát mảng đếm (count array) cho các tập dữ liệu nhỏ ở đáy cây đệ quy.
- Batch Memory Output: Quá trình in kết quả không ghi từng ký tự mà dùng memcpy để chép toàn bộ chuỗi vào bộ đệm đầu ra (out_buf). Khi bộ đệm gần đầy, hệ thống mới xả (flush) một lần bằng fwrite.

# 3. Lý giải tại sao phương pháp này tốt nhất: 

Cách tiếp cận chia để trị theo hai giai đoạn này là giải pháp toàn diện và tối ưu nhất cho biến thể bài toán (sắp xếp theo độ dài trước, từ điển sau) vì những lý do sau:
- Loại bỏ chi phí so sánh độ dài đa luồng: Nếu sử dụng hàm std::sort với một hàm cmp tùy chỉnh (so sánh độ dài trước, nếu bằng nhau thì so sánh chuỗi), CPU sẽ phải thực hiện phép kiểm tra độ dài if (a.len != b.len) lặp đi lặp lại hàng triệu lần trong suốt quá trình phân nhánh của QuickSort. Bằng cách sử dụng Counting Sort (với độ phức tạp O(N)) để phân tách độ dài ngay từ đầu, giai đoạn sắp xếp chuỗi sau đó hoàn toàn không còn gánh nặng phải kiểm tra chiều dài.
- Độ phức tạp thời gian O(N + W): Thuật toán sở hữu thời gian thực thi tiệm cận tuyến tính. Counting Sort mất O(N) thời gian, và MSD Radix Sort duyệt qua các ký tự với chi phí tỷ lệ thuận với tổng số lượng ký tự O(W). Không có sự so sánh lặp lại nào xảy ra như trong các thuật toán so sánh O(N log N).
- Tối đa hóa Cache L1/L2 (Cache-friendliness): Việc định tuyến tất cả con trỏ chuỗi trực tiếp trên mảng một chiều in_buf đảm bảo dữ liệu nằm liên tiếp nhau trên RAM. Khi thuật toán Radix Sort hoặc Insertion Sort truy xuất ký tự để sắp xếp, CPU có thể nạp các khối bộ nhớ vào Cache một cách tuần tự (spatial locality), giảm thiểu triệt để hiện tượng trễ bộ nhớ (Memory Bottleneck).
- An toàn về bộ nhớ: Cấu trúc StringRef chỉ chứa một con trỏ 8-byte và một số nguyên 4-byte. Việc hoán vị trong lúc sắp xếp thực chất chỉ tốn 12 byte bộ nhớ, đảm bảo tốc độ cực cao bất kể độ dài thực tế của chuỗi là 10 hay 100 ký tự.



### II. Cách thức sinh testcase:

## A: Integer Sort


# 1. Cách thức sinh test case được cài đặt
Đoạn code sử dụng thư viện <random> với bộ sinh số ngẫu nhiên mt19937 (Mersenne Twister) được cố định seed là 8888 để sinh ra N = 100000 phần tử cho 5 test case hoàn toàn khác biệt:

•	Test 001: Khởi tạo mảng tăng dần [0, 1, ..., N-1]. Sau đó, dùng vòng lặp swap(a[i], a[i/2]) (với i từ 2 đến N-1) để xáo trộn tạo thành một hoán vị đặc biệt. Cuối cùng, nhân các phần tử với 10000 và đan xen dấu âm/dương (chẵn dương, lẻ âm).

•	Test 002: Tạo một mảng chỉ chứa duy nhất 5 giá trị đặc biệt lặp đi lặp lại: 0, -1, 1, 2147483647 (INT_MAX), và -2147483648 (INT_MIN).

•	Test 003: Sinh ngẫu nhiên phân phối đều (Uniform Distribution) các số nguyên nằm rải rác trên toàn bộ dải giá trị của số nguyên 32-bit có dấu (từ 2^31 đến 2^31- 1).

•	Test 004: Sinh ngẫu nhiên các số nguyên âm có giá trị tuyệt đối rất lớn (từ -10^9 đến -2^31).

•	Test 005: Sử dụng hai mặt nạ bit luân phiên là 0xAAAAAAAA (dãy bit 101010...) và 0x55555555 (dãy bit 010101...). Mỗi giá trị được XOR thêm với một số ngẫu nhiên nhỏ (từ 0 đến 99) để tạo nhiễu.

# 2. Các thuật toán mục tiêu mà bộ test này nhắm tới
Bộ test này không nhắm vào một thuật toán duy nhất mà là một màng lọc để gây khó khăn các nhóm thuật toán sắp xếp phổ biến nhưng cài đặt thiếu tối ưu, bao gồm:

•	Quicksort cơ bản (Naive Quicksort): Các phiên bản Quicksort chọn chốt (pivot) cố định (như phần tử đầu, phần tử cuối, hoặc phần tử ở giữa) và chỉ phân hoạch làm 2 phần (2-way partitioning).

•	Counting Sort / Bucket Sort cơ bản: Thuật toán sắp xếp dựa trên việc đếm tần số xuất hiện của các phần tử và cấp phát mảng phụ dựa trên khoảng giá trị (Max - Min).

•	Radix Sort cơ bản: Thuật toán sắp xếp theo cơ số (thường là cơ số 10 hoặc cơ số 2) mà không tối ưu hóa bộ nhớ đệm (cache).

# 3. Lý do chọn các thuật toán mục tiêu này
Trong các bài toán Benchmark (đánh giá hiệu năng) với giới hạn thời gian và bộ nhớ gắt gao:

•	Quicksort luôn là lựa chọn đầu tiên của mọi người (hoặc dùng thẳng hàm std::sort trong các ngôn ngữ lập trình). Việc nhắm vào Quicksort là để kiểm tra xem người viết có hiểu về các trường hợp xấu nhất (Worst-case) của chia để trị hay không.

•	Counting Sort. Mọi người thường nghĩ sắp xếp số nguyên thì dùng Counting Sort sẽ đạt O(N) nhanh nhất, nhưng lại quên mất bài toán thực tế bị giới hạn bởi không gian bộ nhớ vật lý. Việc nhắm vào thuật toán này để kiểm tra tư duy quản lý tài nguyên.

•	Radix Sort là giải pháp đúng đắn nhất cho bài này để đạt O(N) thực sự. Tuy nhiên, nếu cài đặt Radix Sort sơ sài, người lập trình sẽ không làm chủ được độ trễ của phần cứng. Nhắm vào thuật toán này để phân loại các lập trình viên biết tối ưu hóa mức thấp.

# 4. Tại sao các test trên giúp tăng thời gian chạy của chúng
Mỗi test case là một vũ khí chuyên biệt để ép các thuật toán trên bộc lộ nhược điểm, làm tăng thời gian chạy hoặc trực tiếp gây lỗi hệ thống:

•	Test 001 (Anti-Quicksort): Vòng lặp swap(a[i], a[i/2]) tạo ra một mẫu dữ liệu kinh điển gọi là "Median-of-3 Killer". Nó lừa các bộ chia Quicksort (thường chọn phần tử giữa hoặc trung vị của 3 phần tử làm chốt) liên tục chọn phải phần tử lớn nhất hoặc nhỏ nhất. Điều này khiến cây đệ quy bị lệch hoàn toàn, ép độ phức tạp thời gian từ O(N \log N) suy biến thành O(N^2). Các mốc nhân với 10000 và đổi dấu chỉ để làm dữ liệu trông ngẫu nhiên hơn nhằm đánh lừa các hàm heuristic nếu có.

•	Test 002 (Massive Duplicates & Overflows): Việc chỉ có 5 giá trị lặp lại 100000 lần sẽ đánh gục các bộ Quicksort phân hoạch 2 phần, khiến chúng thực hiện vô số phép hoán vị thừa thãi và đệ quy sâu vô ích, lại đẩy thời gian lên O(N^2). Thêm vào đó, sự xuất hiện của INT_MAX và INT_MIN sẽ gây ra lỗi tràn số nếu thuật toán của mọi người có các phép toán như (a + b) / 2 hoặc Max - Min.

•	Test 003 & 004 (Memory/Time Bomb cho Counting Sort): Dải giá trị trải dài từ -2^31 đến 2^31 - 1. Khoảng cách giữa Min và Max lên tới 2^32. Nếu mọi người dùng Counting Sort, họ sẽ phải cấp phát một mảng đếm có 2^32 phần tử kiểu int. Hệ thống sẽ đòi hỏi khoảng 16 GB RAM. Vì giới hạn của bài là 1024 MB, chương trình sẽ lập tức bị hệ điều hành tước quyền (Memory Limit Exceeded) hoặc bị hoán đổi (swap/page fault) liên tục trên ổ cứng, làm thời gian chạy tăng lên hàng nghìn lần. Test 004 nhấn mạnh vào dải số âm lớn để bẻ gãy các mảng đếm không biết xử lý chỉ số âm.

•	Test 005 (Radix Sort / Cache Miss Thrashing): Các mặt nạ bit 0xAAAAAAAA (toàn bit 1 ở các vị trí chẵn) và 0x55555555 (toàn bit 1 ở các vị trí lẻ) được thiết kế đặc biệt để tối đa hóa sự phân tán. Khi Radix Sort đọc từng byte để phân vào các xô (bucket), các giá trị này sẽ di chuyển qua lại liên tục giữa các vùng nhớ cách xa nhau. Việc xen kẽ thêm một chút nhiễu ngẫu nhiên làm vô hiệu hóa bộ máy dự đoán rẽ nhánh (Branch Predictor) và tạo ra hàng loạt lỗi trượt bộ nhớ đệm (Cache Miss) trên CPU. Điều này làm hỏng tính chất cục bộ không gian (Spatial Locality), khiến chi phí thời gian cho các vòng lặp trong Radix Sort tăng vọt về mặt hằng số.

## B: Lexicographic Sort


# 1. Cách thức sinh test case được cài đặt
Mã nguồn sử dụng một hàm sinh số ngẫu nhiên tùy chỉnh my_rand() (thuật toán Linear Congruential Generator) với hạt giống cố định 987654321 để đảm bảo tính tất định. Hàm toBase26 chuyển một số nguyên thành chuỗi 5 ký tự (từ aaaaa đến zzzzz). Mảng gồm N = 100000 phần tử được sinh qua 5 case test sau:

•	Test 001 (Phân phối xen kẽ đối xứng): Sử dụng tiền tố chung dài 95 ký tự 'a'. Mã nguồn điền các chuỗi có hậu tố tuần tự (base26 tăng dần) vào mảng theo cơ chế đối xứng từ ngoài vào trong (a[i] và a[N - 1 - i]). Kết quả tạo ra một cấu trúc mảng dạng "hình ống" (organ-pipe distribution).

•	Test 002 (Trùng lặp mật độ cao): Tiền tố chung cực dài gồm 99 ký tự 'z'. Mảng chỉ lặp đi lặp lại đúng 4 mẫu chuỗi có ký tự cuối khác biệt (...a, ...z, ...b, ...y).

•	Test 003 (Phân khối giảm dần cục bộ): Chia mảng thành các khối (chunk) nhỏ kích thước 32 phần tử. Mỗi khối dùng chung một tiền tố 99 ký tự (chứa mã base26 của khối và 94 ký tự 'm'). Ký tự cuối cùng trong mỗi khối được sắp xếp giảm dần (từ z lùi về a).

•	Test 004 (Ngẫu nhiên hoàn toàn): Sinh các chuỗi dài 100 ký tự hoàn toàn ngẫu nhiên bằng hàm my_rand(). Đây là bài test kiểm soát (control test).

•	Test 005 (Sắp xếp ngược toàn cục): Sử dụng chung tiền tố 95 ký tự 'x'. Vòng lặp chạy lùi từ N-1 về 0 để tạo ra các hậu tố giảm dần. Kết quả là toàn bộ mảng 10^5 phần tử được sắp xếp theo thứ tự giảm dần nghiêm ngặt.

# 2. Các thuật toán mục tiêu mà bộ test này nhắm tới
Bộ test benchmark này được thiết kế như một "màng lọc" để bẻ gãy các phương pháp giải quyết sau:

•	Quicksort cơ bản (Cài đặt thủ công): Sử dụng cơ chế chọn chốt (pivot) ngây thơ (chọn phần tử đầu, cuối, hoặc giữa) và chỉ phân hoạch 2 phần (2-way partitioning).

•	std::sort mặc định kết hợp với toán tử < của std::string: Thuật toán IntroSort chuẩn của C++ chưa được tinh chỉnh đặc thù cho chuỗi ký tự.

•	Các thuật toán thiếu nhận thức về Tiền tố chung (LCP - Longest Common Prefix): Bất kỳ thuật toán sắp xếp dựa trên so sánh nào coi việc so sánh 2 chuỗi luôn tốn O(1) thời gian.

•	Các thuật toán sao chép chuỗi sâu (Deep Copying): Cài đặt thao tác hoán vị (Swap) bằng cách tạo bản sao chuỗi thay vì tráo đổi con trỏ bộ nhớ (đặc biệt chí mạng vì chuỗi có độ dài 100 vượt qua ngưỡng Small String Optimization - SSO của C++).

# 3. Lý do chọn các thuật toán mục tiêu này
Trong một thử thách về hiệu năng:

•	Kiểm tra kiến thức thực tế về String: Mọi người thường lầm tưởng độ phức tạp của bài toán sắp xếp chuỗi là O(N \log N). Thực tế, chi phí so sánh 2 chuỗi là O(L) với L là độ dài tiền tố giống nhau. Thuật toán mục tiêu số 2 và 3 được chọn để trừng phạt lỗ hổng kiến thức này.

•	Kiểm tra kỹ năng xử lý dữ liệu trùng lặp: Quicksort phân hoạch 2 phần là thuật toán kinh điển được dạy trên trường, nhưng nó sẽ sụp đổ trước dữ liệu trùng lặp. Nhắm vào thuật toán này buộc mọi người phải biết đến cơ chế phân hoạch 3 phần (3-way Radix Quicksort) hoặc các cấu trúc cây tiên tiến (Trie Sort).

•	Đánh giá tư duy tối ưu bộ nhớ: Chuỗi dài 100 ký tự đòi hỏi cấp phát trên bộ nhớ Heap. Nhắm vào thao tác swap/copy (Mục tiêu 4) để sàng lọc những mọi người biết cách sử dụng mảng con trỏ, std::move, hoặc con trỏ tham chiếu thay vì di chuyển dữ liệu thô.

# 4. Tại sao các test trên giúp tăng thời gian chạy của chúng
Đây là phần cốt lõi giải thích sức mạnh của từng test case sinh test:

•	Hiệu ứng Tiền tố chung cực dài (Đóng góp chung vào TLE): Các Test 1, 2, 3, 5 đều chèn vào 94-99 ký tự giống hệt nhau ở đầu. Mỗi lệnh if (a < b) sẽ buộc CPU phải duyệt qua từng ấy ký tự giống nhau mới tìm thấy sự khác biệt ở ký tự cuối. Điều này làm chi phí của mọi phép so sánh tăng lên gấp 100 lần, kéo độ phức tạp lý thuyết của std::sort từ O(N \log N) lên O(N \cdot L \log N).

•	Test 001 (Đánh lừa IntroSort/Median-of-3): Phân phối mảng theo hình ống (organ-pipe) là thiên địch của cơ chế chọn chốt Median-of-3 trong std::sort. Nó làm cho pivot được chọn thường xuyên nằm ở vị trí rất lệch, khiến cây đệ quy mất cân bằng, làm tăng đáng kể số vòng lặp và phép so sánh cần thiết.

•	Test 002 (Bom trùng lặp): Việc chỉ có 4 giá trị lặp lại 25.000 lần mỗi giá trị sẽ bẻ gãy hoàn toàn các hàm Quicksort 2-way. Do không có khả năng gom nhóm các phần tử bằng nhau, thuật toán sẽ liên tục hoán đổi các chuỗi giống hệt nhau và tiếp tục chia nhỏ mảng một cách vô nghĩa, ép thời gian chạy suy biến thành O(N^2 \cdot L).

•	Test 003 (Sát thủ của Insertion Sort): Hầu hết các thư viện sort chuẩn (gồm cả C++) khi chia mảng đến kích thước nhỏ (thường là \le 32) sẽ tự động chuyển sang Insertion Sort. Bằng cách ép các khối 32 phần tử này vào trạng thái giảm dần nghiêm ngặt, thuật toán Insertion Sort cục bộ sẽ phải thực hiện số phép dịch chuyển tối đa O(K^2) cho mỗi khối, làm tắc nghẽn bộ nhớ đệm.

•	Test 004 (Vô hiệu hóa bộ gỡ LCP): Nếu mọi người tối ưu hóa bằng cách bỏ qua các ký tự giống nhau ở đầu (ví dụ dùng MSD Radix Sort để "ăn gian" Test 1, 2, 3, 5), Test 4 với cấu trúc ngẫu nhiên hoàn toàn sẽ tạo ra cây phân nhánh cực kỳ rộng. Khởi tạo mảng động (bucket) liên tục cho 26 ký tự tại mỗi nhánh sẽ gây hao phí tài nguyên cấp phát (Overhead Allocation), khiến các thuật toán này chạy chậm hơn cả thuật toán cơ bản.

•	Test 005 (Nghịch thế toàn cục): Mảng được sắp xếp ngược hoàn toàn. Đây là bài test kinh điển gây tràn bộ nhớ stack (Stack Overflow) do đệ quy quá sâu đối với Quicksort ngây thơ (chọn pivot ở phần tử cuối). Thậm chí với các thuật toán tốt, việc phải hoán vị \approx N/2 phần tử (mỗi phần tử là một đối tượng string dài 100 ký tự trên heap) sẽ bào mòn băng thông bộ nhớ một cách tàn khốc.


## C: Length-aware Lexicographic Sort


# 1. Cách thức sinh test case được cài đặt
Đoạn mã thiết lập N = 10000 và sinh ra 5 test case đặc thù để đánh giá toàn diện hiệu năng:

•	Test 001 (Đồng nhất toàn cục): Mảng chứa 10000 chuỗi giống hệt nhau, mỗi chuỗi gồm 100 ký tự 'x'.

•	Test 002 (Hoán vị chống Quicksort + LCP siêu dài): Đầu tiên, thuật toán tạo một hoán vị "Median-of-3 Killer" thông qua vòng lặp swap(perm[i], perm[i / 2]). Sau đó, mỗi chuỗi được tạo ra có độ dài đúng 100 ký tự: bao gồm một tiền tố chung cực dài (95 ký tự 'a'), nối với 5 ký tự base26 được mã hóa từ mảng hoán vị perm.

•	Test 003 (Độ dài giảm dần + Trùng lặp khối): Thuật toán sinh các chuỗi có độ dài giảm dần nghiêm ngặt từ 100 xuống 10. Tại mỗi mức độ dài, mảng chứa các chuỗi giống hệt nhau (khoảng 109 chuỗi mỗi nhóm), bao gồm toàn các ký tự đồng nhất (ví dụ toàn 'a', toàn 'b').

•	Test 004 (Nghịch thế cục bộ + Tiền tố chung): Mảng được chia thành các khối (chunk) nhỏ kích thước 32. Mỗi khối dùng chung một tiền tố dài 99 ký tự (gồm 5 ký tự mã hóa số thứ tự khối và 94 ký tự 'm'). Ký tự thứ 100 cuối cùng trong mỗi khối được sắp xếp giảm dần (từ 'z' lùi về 'a').

•	Test 005 (Độ dài đan xen/Ziczac): Mảng được lấp đầy bởi các cặp chuỗi đan xen liên tục: một chuỗi cực dài (100 ký tự 'z') đi kèm ngay sau là một chuỗi cực ngắn (10 ký tự 'a').

# 2. Các thuật toán mục tiêu mà bộ test này nhắm tới
Vì bài toán yêu cầu sắp xếp theo 2 tiêu chí ưu tiên (Độ dài \rightarrow Thứ tự từ điển), bộ test này được thiết kế để trừng phạt các cách cài đặt ngây thơ sau:

•	Custom Comparator thiếu tối ưu: Sử dụng hàm so sánh tùy chỉnh bool cmp(string a, string b) gọi a.length() < b.length() sau đó return a < b và truyền trực tiếp vào std::sort.

•	Bucket Sort cục bộ: Thuật toán chia dữ liệu vào các giỏ (bucket) theo độ dài (từ 10 đến 100), sau đó dùng một thuật toán sắp xếp yếu (như Bubble Sort, Insertion Sort, hoặc Quicksort cơ bản) để sort từng giỏ.

•	Thuật toán so sánh không nhận thức được Tiền tố chung (LCP): Bỏ qua thực tế rằng việc so sánh hai chuỗi dài có phần đầu giống nhau sẽ tiêu tốn độ phức tạp O(L), với L là chiều dài tiền tố chung.

•	Cài đặt hoán vị bằng Deep Copy: Cài đặt hàm swap bằng cách gán giá trị (copy object) thay vì tráo đổi con trỏ, gây tràn băng thông bộ nhớ khi xử lý các chuỗi dài 100 ký tự.

# 3. Lý do chọn các thuật toán mục tiêu này

•	Sàng lọc thói quen lạm dụng Thư viện: Đa số mọi người khi gặp bài toán nhiều tiêu chí sẽ lập tức viết Custom Comparator. Tuy nhiên, họ hiếm khi nhận thức được các chi phí chìm (Hidden Costs) bên trong hàm này khi xử lý với số lượng dữ liệu lớn. Nhắm vào mục tiêu 1 để đánh giá khả năng tối ưu hóa cấp độ vi kiến trúc (micro-architecture).

•	Đánh giá tư duy phân tích Worst-case: Nhóm các chuỗi theo độ dài (Bucket Sort) là một hướng đi thông minh. Tuy nhiên, nhắm vào mục tiêu 2 nhằm kiểm tra xem lập trình viên có lường trước được trường hợp dữ liệu bị "nhồi" toàn bộ vào một giỏ duy nhất hay không.

•	Kiểm tra kiến thức về chuỗi (String Manipulation): Chuỗi dài 100 ký tự vượt qua giới hạn Tối ưu hóa chuỗi nhỏ (Small String Optimization - SSO) của C++. Việc copy hay so sánh chúng rất tốn kém tài nguyên Heap. Nhắm vào mục tiêu 3 và 4 để trừng phạt sự thiếu hụt kiến thức quản lý bộ nhớ.

# 4. Tại sao các test trên giúp tăng thời gian chạy của thuật toán (Gây TLE)
Sự kết hợp giữa đặc tính độ dài và cấu trúc dữ liệu trong 5 test case tạo ra những nút thắt cổ chai chí mạng:

•	Test 001 (Vô hiệu hóa Bucket Sort): Bằng cách cho toàn bộ 10000 chuỗi đều có chiều dài 100, phương pháp chia giỏ theo chiều dài trở nên vô nghĩa. Thuật toán bị ép quay trở lại bài toán sắp xếp chuỗi thông thường trên một tập dữ liệu đồng nhất.

•	Test 002 (Sát thủ Quicksort toàn diện): Đây là test case có sức hủy diệt cao nhất. Độ dài 100 ký tự bằng nhau khiến tiêu chí 1 (xét độ dài) bị vô hiệu hóa. Tiếp đó, 95 ký tự 'a' ở đầu ép mỗi lệnh so sánh phải tốn O(L) thời gian. Cuối cùng, hoán vị chống Median-of-3 đánh sập cây phân hoạch của std::sort hoặc Quicksort, đẩy tổng độ phức tạp lên cực đại: O(N^2 \cdot L).

•	Test 003 (Sát thủ tráo đổi): Với thứ tự chiều dài giảm dần nghiêm ngặt toàn mảng, mọi thuật toán có thiên hướng duyệt và đổi chỗ tuần tự (Insertion/Bubble) sẽ phải thực hiện O(N^2) lần hoán vị (Swap). Nếu dùng Deep Copy, bộ nhớ sẽ bị quá tải nặng nề.

•	Test 004 (Bẫy Insertion Sort cục bộ): Tại các khối kích thước \le 32, các thư viện chuẩn (IntroSort) thường kích hoạt Insertion Sort. Việc mảng bị nghịch thế (giảm dần) cục bộ kết hợp với tiền tố chung 99 ký tự bắt CPU phải so sánh và dịch chuyển bộ nhớ liên tục trong không gian hẹp, gây dội Cache (Cache Thrashing).

•	Test 005 (Phá vỡ Bộ dự đoán rẽ nhánh - Branch Predictor): Test case này không tấn công vào số lượng phép toán, mà tấn công thẳng vào phần cứng CPU. Câu lệnh if (a.length() < b.length()) sẽ trả về kết quả True - False xen kẽ liên tục (T-F-T-F...). Pipeline của CPU hiện đại sẽ không thể dự đoán được nhánh mã tiếp theo, dẫn đến việc phải xóa toàn bộ luồng lệnh hàng vạn lần, làm thời gian thực thi có thể tăng gấp 3 đến 5 lần so với dữ liệu ngẫu nhiên thông thường.

### III. Thuật toán cài đặt tốt nhất ở lần thứ 2

## A. Integer Sort

# 1. Thuật toán cài đặt tốt nhất:

Khi đối mặt với bài toán sắp xếp một mảng số nguyên lớn (đặc biệt là trong lập trình thi đấu hoặc xử lý dữ liệu lớn), đây là 3 lựa chọn hàng đầu:Radix Sort (Cơ số 2^{16} = 65536): Đây chính là thuật toán bạn đang dùng. Với số nguyên 32-bit, chia làm 2 lượt đi (2 passes), độ phức tạp là O(N). Nó nhanh hơn rất nhiều so với các thuật toán dựa trên phép so sánh khi N lớn, vì số lượt duyệt cố định là 2 thay vì \log N.std::sort (Introsort - Kết hợp giữa Quick Sort, Heap Sort và Insertion Sort): Thuật toán mặc định của C++. Độ phức tạp O(N \log N). Dù về mặt lý thuyết chậm hơn Radix Sort, nhưng nhờ các công nghệ tối ưu hóa nội tại của compiler (như SIMD, loop unrolling), std::sort vẫn chạy cực kỳ nhanh và là lựa chọn "an toàn" nhất nếu không muốn tự cài đặt.Counting Sort: Độ phức tạp O(N + K) với K là khoảng giá trị của phần tử. Thuật toán này chỉ tốt nhất khi giá trị các phần tử nhỏ (ví dụ A_i \le 10^6). Nếu khoảng giá trị rộng (từ -2 \cdot 10^9 đến 2 \cdot 10^9), Counting Sort hoàn toàn bất khả thi vì tràn bộ nhớ.Kết luận cho Mục 1: Lựa chọn Radix Sort với cơ số 65536 của bạn là tối ưu nhất về mặt tốc độ lý thuyết cho một mảng số nguyên 32-bit ngẫu nhiên diện rộng.

# 2. Các phương thức liên quan đến thuật toán chính (Radix Sort):
Để Radix Sort chạy mượt mà với số nguyên có dấu (signed int), hàm radixSort của bạn phối hợp các kỹ thuật sau:Phép biến đổi Bit Biểu diễn (a[i] ^= 0x80000000): Bản chất của số nguyên có dấu trong máy tính dùng mã bù 2, khiến số âm có bit cao nhất (bit dấu) là 1, còn số dương là 0. Phép ^= 0x80000000 sẽ đảo ngược bit dấu này, biến các số âm thành các số "nhỏ hơn" số dương trong hệ không dấu (unsigned), giúp thuật toán sắp xếp đúng thứ tự. Cuối hàm ta chỉ cần đảo lại một lần nữa.Mảng đếm tần suất (count1, count2 kích thước 65536): Thay vì đếm từng chữ số hệ 10, ta đếm theo cụm 16 bit. 2^{16} = 65536, vừa vặn với một mảng kích thước nhỏ, tối ưu bộ nhớ cache của CPU.Kỹ thuật lấy 16 bit thấp và 16 bit cao:Lượt 1: a[i] & 0xFFFF để trích xuất 16 bit cuối.Lượt 2: (b[i] >> 16) & 0xFFFF để dịch phải và lấy 16 bit đầu.Mảng cộng dồn (Prefix Sum) và phân phối ngược: Tính vị trí bắt đầu của các nhóm số và duyệt ngược từ n - 1 về 0 để đảm bảo tính ổn định (stable sort) của thuật toán.

# 3. tối ưu tiếp tục so với lần 1:
# + Quản lý bộ nhớ (Mảng dữ liệu): 
    - Bài cũ: Cấp phát động: new int[n]
    - Bài mới: Mảng toàn cục cố định: int data_arr[100005]
    - Đánh giá: Bài cũ linh hoạt hơn! Bài mới bị giới hạn cứng N≤105. Nếu đề bài cho N=106, bài mới sẽ bị lỗi tràn mảng (Runtime Error) ngay lập tức.
# + An toàn phép dịch bit:
    - Bài cũ: Thao tác trực tiếp trên int có dấu.
    - Bài mới: Ép kiểu sang unsigned int*.
    - Đánh giá: Bài mới xuất sắc! Dịch phải (>>) trên số int có dấu có thể kích hoạt arithmetic shift (giữ lại bit dấu), gây sai số. Ép sang unsigned int đảm bảo luôn là logical shift (điền số 0 vào bên trái).
# + Xử lý tràn số khi in/đọc số âm:
    - Bài cũ: Dùng int: x = -x;
    - Bài mới: Dùng long long: lx = -lx;
    - Đánh giá: Bài mới sửa lỗi chí mạng! Ở bài cũ, nếu số đầu vào là INT_MIN (−2147483648), phép x = -x sẽ gây tràn số nghiêm trọng vì số dương lớn nhất chỉ là 2147483647. Bài mới dùng long long đã triệt tiêu hoàn toàn lỗi này.
# + Tốc độ thực thi:
    - Bài cũ: Khá nhanh.
    - Bài mới: Nhanh hơn một chút ở khâu I/O.
    - Đánh giá: Việc khai báo mảng toàn cục (bản mới) giúp tiết kiệm vài mili-giây cấp phát vùng nhớ Heap so với  (bản cũ).
 
## B: Lexicographic Sort

# 1. Thuật toán cài đặt tốt nhất:
Khác với sắp xếp số nguyên, sắp xếp chuỗi có đặc thù là phép so sánh tốn chi phí tỷ lệ thuận với độ dài chuỗi (O(L)). Dưới đây là các thuật toán hàng đầu:MSD Radix Sort (Sắp xếp theo cơ số từ trái sang phải): Đây là thuật toán bạn đang sử dụng và cũng là lựa chọn tối ưu nhất cho dữ liệu chuỗi lớn. Nó nhóm các chuỗi theo ký tự đầu tiên, sau đó đệ quy xuống để sắp xếp theo các ký tự tiếp theo. Độ phức tạp là O(W \cdot N), với W là độ dài trung bình để phân biệt các chuỗi. Burstsort / Trie Sort: Thay vì chia mảng, thuật toán này đưa các chuỗi vào một cấu trúc dữ liệu dạng cây (Trie). Burstsort là phiên bản tối ưu cache của Trie Sort và hiện được coi là thuật toán sắp xếp chuỗi nhanh nhất thế giới trên thực tế. Tuy nhiên, nó cực kỳ phức tạp để tự cài đặt trong các kỳ thi.3-way Radix Quicksort (Quicksort 3 phân thủy): Lai giữa Quicksort và MSD Radix Sort. Ở mỗi bước, nó chọn một ký tự pivot và chia mảng làm 3 phần: nhỏ hơn, bằng, và lớn hơn pivot. Rất phù hợp nếu các chuỗi có nhiều tiền tố chung dài, tránh được chi phí tạo mảng tần suất của Radix Sort.std::sort (C++): Sử dụng std::sort kết hợp với std::string. Độ phức tạp là O(N \log N \cdot L). Chậm hơn đáng kể vì cache miss và chi phí cấp phát bộ nhớ (allocation) của std::string nếu không được tối ưu.Kết luận: MSD Radix Sort là thuật toán "công thủ toàn diện", cực kỳ xuất sắc cho bài toán này, đặc biệt khi bạn đã kết hợp nó với Custom I/O.

# 2. Các phương thức liên quan đến thuật toán chính (MSD Radix Sort):
Để MSD Radix Sort đạt tốc độ bàn thờ và không bị lỗi, code của bạn đã áp dụng một loạt các kỹ thuật lõi sau:Nhóm theo ký tự (Bucketing): Đếm tần suất (Counting Sort) ký tự tại vị trí d (index d). Dựa vào tần suất, thuật toán chia mảng thành các phân nhóm (buckets).Ký tự Null (\0): Khi một chuỗi ngắn hơn chuỗi khác (ví dụ "abc" và "abcd"), chuỗi ngắn phải đứng trước. Việc gán giá trị kết thúc chuỗi \0 vào vị trí bucket đầu tiên (index 0) xử lý hoàn hảo trường hợp này.Chuyển đổi chiến thuật (Fallback to Insertion Sort): Đây là tối ưu quan trọng nhất của thuật toán. Khi một nhóm đệ quy có số lượng phần tử quá nhỏ (code bạn chọn N \le 16), overhead (chi phí) của việc khởi tạo mảng tần suất (count) lớn hơn nhiều so với việc sắp xếp so sánh. Việc chuyển sang Insertion Sort giúp thuật toán chạy nhanh hơn 15% - 20%.Cấu trúc dữ liệu Memory Pool: Thay vì cấp phát hàng vạn std::string nằm rải rác trong Heap, bạn ném toàn bộ ký tự vào một mảng 1 chiều khổng lồ (pool). Các đối tượng Ref (hoặc StringRef) chỉ lưu con trỏ (char*) trỏ vào mảng đó. Điều này giúp tối đa hóa tốc độ đọc của Cache L1/L2 trên CPU.

# 3. tối ưu tiếp tục so với lần 1:
# + Kích thước bảng chữ cái (Alphabet Size): 
    - Bài cũ: 256 (Toàn bộ bảng mã ASCII).
    - Bài mới: 27 (Chỉ chữ cái thường 'a'-'z' và \0).
    - Đánh giá: Bài mới chạy nhanh hơn rất nhiều! Mỗi lần đệ quy, bài cũ phải cấp phát và duyệt mảng kích thước 256. Bài mới chỉ duyệt 27. Tuy nhiên, bài mới sẽ sai nếu input có chữ hoa, số hoặc ký tự đặc biệt.
# + Quản lý bộ nhớ:
    - Bài cũ: Dùng new cấp phát động theo N.
    - Bài mới: Dùng mảng hằng số toàn cục POOL_SIZE = 11000000, MAX_N = 100000.
    - Đánh giá: Tương tự bài số nguyên. Bài mới loại bỏ được thời gian xin cấp bộ nhớ của HĐH (rất nhanh), nhưng bị khóa cứng giới hạn dữ liệu. Bạn phải tự đảm bảo tổng số ký tự không vượt 11 triệu.
# + Hàm so sánh (Fallback):
    - Bài cũ: Tận dụng thư viện <cstring>: strcmp.
    - Bài mới: Tự viết tay hoàn toàn: lessStr và insertionSort.
    - Đánh giá: Bài mới linh hoạt hơn. Việc viết hàm lessStr có thêm tham số d giúp nó bỏ qua việc so sánh lại từ đầu những tiền tố (prefix) đã được đảm bảo là giống nhau ở các vòng đệ quy trước, tối ưu hơn strcmp thông thường một chút.
# + Tối ưu vòng lặp chia Bucket:
    - Bài cũ: Duyệt qua chuỗi, tính toán end - start > 1.
    - Bài mới: Lưu sẵn vị trí mảng pos[27] và cur[27].
    - Đánh giá: Bài mới viết code "sạch" và tiêu chuẩn hơn. Logic lưu vị trí đầu vào của bucket (pos[i]) giúp tránh phải thao tác tính toán offset nhọc nhằn, dễ debug hơn hẳn so với bài cũ.

## C. Length-aware Lexicographic String Sort
# 1. Các thuật toán tốt nhất:
Lựa chọn tốt nhất:Length-Bucketing + MSD Radix Sort: Đây chính là chiến thuật của Bài cũ. Nó cực kỳ tối ưu vì nhóm các chuỗi cùng chiều dài lại với nhau bằng Counting Sort (độ phức tạp O(N)), sau đó chỉ chạy Radix Sort trên các chuỗi có cùng chiều dài. Không có thuật toán so sánh nào có thể vượt qua cách này về mặt tốc độ.std::sort với Custom Comparator: Dùng hàm std::sort có sẵn của C++ kết hợp với hàm so sánh tùy chỉnh (giống hàm isSmaller của bạn). Thuật toán bên dưới là Introsort (chạy cực nhanh, không tốn thêm bộ nhớ). Độ phức tạp O(N \log N \cdot L).Merge Sort (Thuật toán Bài mới): Cũng giải quyết tốt bài toán nhờ tính ổn định, độ phức tạp O(N \log N \cdot L). Tuy nhiên, nó tiêu tốn thêm bộ nhớ cho mảng phụ (tmpArr) và chậm hơn std::sort do không được tối ưu ở mức compiler.Kết luận: Xét về tốc độ tuyệt đối, thuật toán của Bài cũ là "vô địch". Xét về độ an toàn và dễ code, dùng std::sort của C++ là tốt nhất. Tự viết Merge Sort như Bài mới nằm ở mức trung bình.

# 2. Các phương thức liên quan:
Với Bài cũ (Length-Bucketing + MSD Radix Sort) Phân lô theo chiều dài (Length Offset): Thuật toán dùng 2 mảng len_count và len_offset để tính toán chính xác vị trí của từng chuỗi trong mảng sorted_by_len chỉ thông qua độ dài của chúng. Đây là kỹ thuật Prefix-Sum kinh điển, giúp triệt tiêu hoàn toàn việc phải đi so sánh 2 chuỗi lệch độ dài. Zero-Copy (Tham chiếu vùng nhớ): Struct StringRef chỉ lưu con trỏ char* s trỏ thẳng vào bộ đệm nhập liệu (in_buf) và độ dài len. Nó không hề tạo ra một bản sao chuỗi nào trong bộ nhớ, tối đa hóa hiệu năng.Tối ưu chặn dưới (Threshold): Dùng Insertion Sort và strcmp khi số lượng phần tử cần đệ quy N < 25.Với Bài mới (Merge Sort)Custom Comparator (isSmaller): Trái tim của bài mới nằm ở hàm này. Nó định tuyến rõ ràng: So sánh .length() trước, nếu khác nhau thì chuỗi ngắn hơn đứng trước. Nếu bằng nhau, nó trả về kết quả của toán tử < (chuẩn so sánh từ điển của std::string).Cơ chế chia để trị (Divide and Conquer): Liên tục chia đôi mảng vector<string> ra cho đến khi còn 1 phần tử, sau đó gọi hàm doMerge để trộn 2 mảng con đã sắp xếp lại với nhau. Cần một mảng tmpArr để hứng dữ liệu tạm.

# 3. tối ưu tiếp tục so với lần 1:
# + Quản lý bộ nhớ: 
    - Bài cũ: Zero-copy. Chỉ dùng con trỏ trỏ vào vùng nhớ đệm chung 16MB.
    - Bài mới: Cấp phát động liên tục bằng std::string và vector.
    - Đánh giá: Bài cũ hủy diệt Bài mới. Khai báo hàng vạn std::string sẽ khiến HĐH phải cấp phát bộ nhớ rải rác (Heap Allocation), gây nghẽn cổ chai cực nặng và dội Cache Miss liên tục.
# + I/O (Đọc/Ghi):
    - Bài cũ: Đọc 1 cục 16MB vào RAM bằng cin.read, tự phân tách thủ công.
    - Bài mới: Dùng cin >> arr[i] chuẩn của C++.
    - Đánh giá: Bài cũ nhanh gấp hàng chục lần. Dù Bài mới đã bật cin.tie(0), tốc độ khởi tạo std::string qua toán tử >> vẫn không thể đọ lại việc đọc thô theo block byte.
# + Thuật toán cốt lõi:
    - Bài cũ: Nhóm độ dài O(N) + Radix O(W⋅N).
    - Bài mới: Merge Sort O(NlogN⋅L).
    - Đánh giá: Bài cũ có Big-O tốt hơn hẳn. Khi N lên đến 105, NlogN bắt đầu bộc lộ sự chậm chạp so với hàm tuyến tính của Radix.
# + Tính ứng dụng & Bảo trì:
    - Bài cũ: Cực kỳ khó đọc, khó sửa. Dễ dính lỗi Segfault nếu input dị (ví dụ vượt 16MB).
    - Bài mới: Code sạch, rõ ràng, dễ bảo trì, dễ hiểu, chạy an toàn với mọi kích thước input.
    - Đánh giá: Bài mới áp đảo về tính "Con người". Bài mới là mẫu code chuẩn mực khi đi làm thực tế hoặc phỏng vấn, nơi sự trong sáng của logic được đánh giá cao hơn vài mili-giây hiệu năng.
