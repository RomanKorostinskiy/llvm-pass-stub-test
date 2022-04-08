; ModuleID = '<stdin>'
source_filename = "../tests/intrinsics.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: nofree noinline nounwind uwtable
define i32 @main() local_unnamed_addr #0 {
  %1 = alloca <4 x i32>, align 16
  %2 = alloca <4 x i32>, align 16
  %3 = bitcast <4 x i32>* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %3) #4
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(16) %3, i8 0, i64 16, i1 false)
  %4 = bitcast <4 x i32>* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %4) #4
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(16) %4, i8 0, i64 16, i1 false)
  %5 = getelementptr inbounds <4 x i32>, <4 x i32>* %1, i64 0, i64 0
  %6 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %5)
  %7 = getelementptr inbounds <4 x i32>, <4 x i32>* %2, i64 0, i64 0
  %8 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %7)
  %9 = getelementptr inbounds <4 x i32>, <4 x i32>* %1, i64 0, i64 1
  %10 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %9)
  %11 = getelementptr inbounds <4 x i32>, <4 x i32>* %2, i64 0, i64 1
  %12 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %11)
  %13 = getelementptr inbounds <4 x i32>, <4 x i32>* %1, i64 0, i64 2
  %14 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %13)
  %15 = getelementptr inbounds <4 x i32>, <4 x i32>* %2, i64 0, i64 2
  %16 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %15)
  %17 = getelementptr inbounds <4 x i32>, <4 x i32>* %1, i64 0, i64 3
  %18 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %17)
  %19 = getelementptr inbounds <4 x i32>, <4 x i32>* %2, i64 0, i64 3
  %20 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* nonnull %19)
  %21 = load <4 x i32>, <4 x i32>* %1, align 16, !tbaa !3
  %22 = shufflevector <4 x i32> %21, <4 x i32> poison, <4 x i32> <i32 3, i32 2, i32 1, i32 0>
  %23 = sitofp <4 x i32> %22 to <4 x float>
  %24 = load <4 x i32>, <4 x i32>* %2, align 16, !tbaa !3
  %25 = shufflevector <4 x i32> %24, <4 x i32> poison, <4 x i32> <i32 3, i32 2, i32 1, i32 0>
  %26 = sitofp <4 x i32> %25 to <4 x float>
  %27 = bitcast <4 x float> %23 to <4 x i32>
  %28 = bitcast <4 x float> %26 to <4 x i32>
  %29 = icmp eq <4 x i32> %27, %28
  %30 = sext <4 x i1> %29 to <4 x i32>
  %31 = bitcast <4 x i32> %30 to <16 x i8>
  %32 = icmp slt <16 x i8> %31, zeroinitializer
  %33 = bitcast <16 x i1> %32 to i16
  %34 = zext i16 %33 to i32
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %4) #4
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %3) #4
  ret i32 %34
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly nofree nosync nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: nofree nounwind
declare noundef i32 @__isoc99_scanf(i8* nocapture noundef readonly, ...) local_unnamed_addr #3

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

attributes #0 = { nofree noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="128" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { argmemonly nofree nosync nounwind willreturn writeonly }
attributes #3 = { nofree nounwind "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"Ubuntu clang version 12.0.0-3ubuntu1~20.04.5"}
!3 = !{!4, !4, i64 0}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
