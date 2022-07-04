; ModuleID = 'temporary_ir.ll'
source_filename = "comp"

%struct.timeval.0 = type { i64, i64 }

@0 = weak unnamed_addr constant [25 x i8] c"error: memory violation\0A\00"
@1 = weak unnamed_addr constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare void @exit(i32)

declare i64* @memcpy(i32*, i32*, i32)

declare i32 @gettimeofday(%struct.timeval.0*, i8*)

define i32 @get_time() {
entry:
  %0 = alloca %struct.timeval.0, align 8
  %1 = call i32 @gettimeofday(%struct.timeval.0* %0, i8* null)
  %strct.first = getelementptr %struct.timeval.0, %struct.timeval.0* %0, i32 0, i32 0
  %strct.second = getelementptr %struct.timeval.0, %struct.timeval.0* %0, i32 0, i32 1
  %2 = load i64, i64* %strct.second, align 4
  %3 = trunc i64 %2 to i32
  ret i32 %3
}

define void @__check_bounds__(i32 %0, i32 %1) {
entry:
  %2 = icmp sge i32 %0, %1
  br i1 %2, label %memory_err, label %memory_ok

memory_err:                                       ; preds = %entry
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @0, i32 0, i32 0))
  call void @exit(i32 1)
  ret void

memory_ok:                                        ; preds = %entry
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
entry:
  %0 = call i32 @get_time()
  %arr = alloca i32, i32 1000, align 4
  br label %entry.while.cond

entry.while.cond:                                 ; preds = %entry.while.start, %entry
  %index.0 = phi i32 [ 0, %entry ], [ %1, %entry.while.start ]
  %cmp = icmp slt i32 %index.0, 1000
  br i1 %cmp, label %entry.while.start, label %entry.while.end

entry.while.start:                                ; preds = %entry.while.cond
  %1 = add i32 %index.0, 1
  br label %entry.while.cond

entry.while.end:                                  ; preds = %entry.while.cond
  %end_time = alloca i32, align 4
  %2 = call i32 @get_time()
  store i32 %2, i32* %end_time, align 4
  %3 = load i32, i32* %end_time, align 4
  %4 = sub i32 %3, %0
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), i32 %4)
  ret i32 0
}
