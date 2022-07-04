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
  %arr = alloca i32, i32 8, align 4
  %0 = getelementptr i32, i32* %arr, i32 0
  store i32 4, i32* %0, align 4
  %1 = getelementptr i32, i32* %arr, i32 1
  store i32 3, i32* %1, align 4
  %2 = getelementptr i32, i32* %arr, i32 2
  store i32 5, i32* %2, align 4
  %3 = getelementptr i32, i32* %arr, i32 3
  store i32 2, i32* %3, align 4
  %4 = getelementptr i32, i32* %arr, i32 4
  store i32 1, i32* %4, align 4
  %5 = getelementptr i32, i32* %arr, i32 5
  store i32 3, i32* %5, align 4
  %6 = getelementptr i32, i32* %arr, i32 6
  store i32 2, i32* %6, align 4
  %7 = getelementptr i32, i32* %arr, i32 7
  store i32 3, i32* %7, align 4
  %stack = alloca i32, i32 8, align 4
  %8 = call i32 @get_time()
  %9 = getelementptr i32, i32* %stack, i32 0
  store i32 7, i32* %9, align 4
  %10 = getelementptr i32, i32* %stack, i32 1
  store i32 0, i32* %10, align 4
  br label %entry.while.cond

entry.while.cond:                                 ; preds = %entry.while.start.while.end.endif.endif, %entry
  %top.0 = phi i32 [ 1, %entry ], [ %top.2, %entry.while.start.while.end.endif.endif ]
  %cmp = icmp sge i32 %top.0, 0
  br i1 %cmp, label %entry.while.start, label %entry.while.end

entry.while.start:                                ; preds = %entry.while.cond
  %11 = getelementptr i32, i32* %stack, i32 %top.0
  %12 = load i32, i32* %11, align 4
  %13 = sub i32 %top.0, 1
  call void @__check_bounds__(i32 %13, i32 8)
  %14 = getelementptr i32, i32* %stack, i32 %13
  %15 = load i32, i32* %14, align 4
  %16 = sub i32 %13, 1
  %x = alloca i32, align 4
  call void @__check_bounds__(i32 %12, i32 8)
  %17 = getelementptr i32, i32* %arr, i32 %12
  %18 = load i32, i32* %17, align 4
  store i32 %18, i32* %x, align 4
  %i = alloca i32, align 4
  %19 = sub i32 %15, 1
  store i32 %19, i32* %i, align 4
  %j = alloca i32, align 4
  store i32 %15, i32* %j, align 4
  %kk = alloca i32, align 4
  %20 = sub i32 %12, 1
  store i32 %20, i32* %kk, align 4
  %21 = load i32, i32* %kk, align 4
  %22 = load i32, i32* %x, align 4
  %j.promoted = load i32, i32* %j, align 4
  %i.promoted = load i32, i32* %i, align 4
  br label %entry.while.start.while.cond

entry.while.end:                                  ; preds = %entry.while.cond
  %end_time = alloca i32, align 4
  %23 = call i32 @get_time()
  store i32 %23, i32* %end_time, align 4
  %ii1 = alloca i32, align 4
  store i32 0, i32* %ii1, align 4
  %24 = load i32, i32* %end_time, align 4
  %25 = sub i32 %24, %8
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), i32 %25)
  ret i32 0

entry.while.start.while.cond:                     ; preds = %entry.while.start.while.start.endif, %entry.while.start
  %27 = phi i32 [ %58, %entry.while.start.while.start.endif ], [ %i.promoted, %entry.while.start ]
  %28 = phi i32 [ %59, %entry.while.start.while.start.endif ], [ %j.promoted, %entry.while.start ]
  %29 = icmp sle i32 %28, %21
  br i1 %29, label %entry.while.start.while.start, label %entry.while.start.while.end

entry.while.start.while.start:                    ; preds = %entry.while.start.while.cond
  call void @__check_bounds__(i32 %28, i32 8)
  %30 = getelementptr i32, i32* %arr, i32 %28
  %31 = load i32, i32* %30, align 4
  %32 = icmp sle i32 %31, %22
  br i1 %32, label %entry.while.start.while.start.if, label %entry.while.start.while.start.endif

entry.while.start.while.end:                      ; preds = %entry.while.start.while.cond
  %.lcssa1 = phi i32 [ %27, %entry.while.start.while.cond ]
  %.lcssa = phi i32 [ %28, %entry.while.start.while.cond ]
  store i32 %.lcssa, i32* %j, align 4
  store i32 %.lcssa1, i32* %i, align 4
  %temp1 = alloca i32, align 4
  %33 = load i32, i32* %i, align 4
  %34 = add i32 %33, 1
  call void @__check_bounds__(i32 %34, i32 8)
  %35 = getelementptr i32, i32* %arr, i32 %34
  %36 = load i32, i32* %35, align 4
  store i32 %36, i32* %temp1, align 4
  %37 = load i32, i32* %i, align 4
  %38 = add i32 %37, 1
  call void @__check_bounds__(i32 %38, i32 8)
  %39 = getelementptr i32, i32* %arr, i32 %38
  call void @__check_bounds__(i32 %12, i32 8)
  %40 = getelementptr i32, i32* %arr, i32 %12
  %41 = load i32, i32* %40, align 4
  store i32 %41, i32* %39, align 4
  call void @__check_bounds__(i32 %12, i32 8)
  %42 = getelementptr i32, i32* %arr, i32 %12
  %43 = load i32, i32* %temp1, align 4
  store i32 %43, i32* %42, align 4
  %p = alloca i32, align 4
  %44 = load i32, i32* %i, align 4
  %45 = add i32 %44, 1
  store i32 %45, i32* %p, align 4
  %p1 = alloca i32, align 4
  %46 = load i32, i32* %p, align 4
  %47 = sub i32 %46, 1
  store i32 %47, i32* %p1, align 4
  %48 = load i32, i32* %p1, align 4
  %49 = icmp sgt i32 %48, %15
  br i1 %49, label %entry.while.start.while.end.if, label %entry.while.start.while.end.endif

entry.while.start.while.start.if:                 ; preds = %entry.while.start.while.start
  %50 = add i32 %27, 1
  %temp = alloca i32, align 4
  call void @__check_bounds__(i32 %50, i32 8)
  %51 = getelementptr i32, i32* %arr, i32 %50
  %52 = load i32, i32* %51, align 4
  store i32 %52, i32* %temp, align 4
  call void @__check_bounds__(i32 %50, i32 8)
  %53 = getelementptr i32, i32* %arr, i32 %50
  call void @__check_bounds__(i32 %28, i32 8)
  %54 = getelementptr i32, i32* %arr, i32 %28
  %55 = load i32, i32* %54, align 4
  store i32 %55, i32* %53, align 4
  call void @__check_bounds__(i32 %28, i32 8)
  %56 = getelementptr i32, i32* %arr, i32 %28
  %57 = load i32, i32* %temp, align 4
  store i32 %57, i32* %56, align 4
  br label %entry.while.start.while.start.endif

entry.while.start.while.start.endif:              ; preds = %entry.while.start.while.start.if, %entry.while.start.while.start
  %58 = phi i32 [ %50, %entry.while.start.while.start.if ], [ %27, %entry.while.start.while.start ]
  %59 = add i32 %28, 1
  br label %entry.while.start.while.cond

entry.while.start.while.end.if:                   ; preds = %entry.while.start.while.end
  %60 = add i32 %16, 1
  call void @__check_bounds__(i32 %60, i32 8)
  %61 = getelementptr i32, i32* %stack, i32 %60
  store i32 %15, i32* %61, align 4
  %62 = add i32 %60, 1
  call void @__check_bounds__(i32 %62, i32 8)
  %63 = getelementptr i32, i32* %stack, i32 %62
  %64 = load i32, i32* %p, align 4
  %65 = sub i32 %64, 1
  store i32 %65, i32* %63, align 4
  br label %entry.while.start.while.end.endif

entry.while.start.while.end.endif:                ; preds = %entry.while.start.while.end.if, %entry.while.start.while.end
  %top.1 = phi i32 [ %62, %entry.while.start.while.end.if ], [ %16, %entry.while.start.while.end ]
  %p2 = alloca i32, align 4
  %66 = load i32, i32* %p, align 4
  %67 = add i32 %66, 1
  store i32 %67, i32* %p2, align 4
  %68 = load i32, i32* %p2, align 4
  %69 = icmp slt i32 %68, %12
  br i1 %69, label %entry.while.start.while.end.endif.if, label %entry.while.start.while.end.endif.endif

entry.while.start.while.end.endif.if:             ; preds = %entry.while.start.while.end.endif
  %70 = add i32 %top.1, 1
  call void @__check_bounds__(i32 %70, i32 8)
  %71 = getelementptr i32, i32* %stack, i32 %70
  %72 = load i32, i32* %p, align 4
  %73 = add i32 %72, 1
  store i32 %73, i32* %71, align 4
  %74 = add i32 %70, 1
  call void @__check_bounds__(i32 %74, i32 8)
  %75 = getelementptr i32, i32* %stack, i32 %74
  store i32 %12, i32* %75, align 4
  br label %entry.while.start.while.end.endif.endif

entry.while.start.while.end.endif.endif:          ; preds = %entry.while.start.while.end.endif.if, %entry.while.start.while.end.endif
  %top.2 = phi i32 [ %74, %entry.while.start.while.end.endif.if ], [ %top.1, %entry.while.start.while.end.endif ]
  br label %entry.while.cond
}
