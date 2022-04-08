; ModuleID = '<stdin>'
source_filename = "../tests/example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define i32 @foo(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  ret i32 1
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @bar(i32 %0, i32 %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  ret i32 2
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @bar1(i32 %0, i32 %1, i32 %2, i32 %3) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 %0, i32* %5, align 4
  store i32 %1, i32* %6, align 4
  store i32 %2, i32* %7, align 4
  store i32 %3, i32* %8, align 4
  %9 = call i32 @bar(i32 1, i32 2)
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @foo1(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = sitofp i32 %3 to double
  %5 = call double @sqrt(double %4) #2
  %6 = fptosi double %5 to i32
  ret i32 %6
}

; Function Attrs: nounwind
declare double @sqrt(double) #1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @qq(double %0, i32 (i32, i32, i32)* %1) #0 {
  %3 = alloca double, align 8
  %4 = alloca i32 (i32, i32, i32)*, align 8
  store double %0, double* %3, align 8
  store i32 (i32, i32, i32)* %1, i32 (i32, i32, i32)** %4, align 8
  %5 = load double, double* %3, align 8
  %6 = fptosi double %5 to i32
  %7 = load double, double* %3, align 8
  %8 = fmul double 2.000000e+00, %7
  %9 = fptosi double %8 to i32
  %10 = call i32 @bar(i32 %6, i32 %9)
  %11 = call i32 @foo(i32 42)
  %12 = add nsw i32 %10, %11
  %13 = load i32 (i32, i32, i32)*, i32 (i32, i32, i32)** %4, align 8
  %14 = call i32 %13(i32 1, i32 2, i32 3)
  %15 = add nsw i32 %12, %14
  %16 = call i32 @bar1(i32 1, i32 2, i32 3, i32 4)
  %17 = add nsw i32 %15, %16
  ret i32 %17
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"Ubuntu clang version 12.0.0-3ubuntu1~20.04.5"}
