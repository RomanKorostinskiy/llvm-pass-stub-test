; ModuleID = '<stdin>'
source_filename = "tests/example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline norecurse nounwind readnone uwtable willreturn
define i32 @foo(i32 %0) local_unnamed_addr #0 {
  ret i32 1
}

; Function Attrs: noinline norecurse nounwind readnone uwtable willreturn
define i32 @bar(i32 %0, i32 %1) local_unnamed_addr #0 {
  ret i32 2
}

; Function Attrs: noinline norecurse nounwind readnone uwtable willreturn
define i32 @bar1(i32 %0, i32 %1, i32 %2, i32 %3) local_unnamed_addr #0 {
  ret i32 2
}

; Function Attrs: noinline nounwind uwtable
define i32 @qq(double %0, i32 (i32, i32, i32)* nocapture %1) local_unnamed_addr #1 {
  %3 = tail call i32 %1(i32 1, i32 2, i32 3) #2
  %4 = add nsw i32 %3, 5
  ret i32 %4
}

; Function Attrs: noinline norecurse nounwind readnone uwtable willreturn
define i32 @main() local_unnamed_addr #0 {
  ret i32 0
}

attributes #0 = { noinline norecurse nounwind readnone uwtable willreturn "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"Ubuntu clang version 12.0.0-3ubuntu1~20.04.5"}
