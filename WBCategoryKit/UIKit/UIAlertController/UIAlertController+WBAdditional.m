//
//  UIAlertController+WBAdditional.m
//  WBCategories
//
//  Created by wenbo on 2018/5/22.
//  Copyright © 2018年 WENBO. All rights reserved.
//

#import "UIAlertController+WBAdditional.h"

#define kWBCameraDeniedMessage [NSString stringWithFormat:@"请在iPhone的“设置”-“隐私”-“相机”功能中，找到“%@”打开相机访问权",[[NSBundle mainBundle].infoDictionary objectForKey:@"CFBundleName"]]

#define kWBPhotoLibraryDeniedMessage [NSString stringWithFormat:@"请在iPhone的“设置”-“隐私”-“照片”功能中，找到“%@”打开照片访问权",[[NSBundle mainBundle].infoDictionary objectForKey:@"CFBundleName"]]

@implementation UIAlertController (WBAdditional)

+ (void)wb_showAlertWithTitle:(NSString *)title
                      message:(NSString *)message
                 clickedBlock:(WBAlertClickedBlock)clickedBlock
           cancelActionString:(NSString *)cancelActionString
            otherActionString:(NSString *)otherActionString, ... {
    NSMutableArray *argsArray = @[].mutableCopy;
    if (cancelActionString) [argsArray addObject:cancelActionString];
    NSString *arg;
    va_list arg_list;
    if (otherActionString) {
        [argsArray addObject:otherActionString];
        va_start(arg_list, otherActionString);
        while ((arg = va_arg(arg_list,NSString *))) {
            [argsArray addObject:arg];
        }
        va_end(arg_list);
    }
    NSAssert(argsArray.count > 0, @"请设置弹出框按钮标题");
    if ([self isiOS8OrLater]) {
        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title
                                                                         message:message
                                                                  preferredStyle:UIAlertControllerStyleAlert];
        for (NSInteger index = 0; index < argsArray.count; index ++) {
            UIAlertActionStyle style = UIAlertActionStyleDefault;
            if (index == 0 && cancelActionString) {
                style = UIAlertActionStyleCancel;
            }
            UIAlertAction *action = [UIAlertAction actionWithTitle:argsArray[index]
                                                             style:style
                                                           handler:^(UIAlertAction * _Nonnull action) {
                                                               clickedBlock ? clickedBlock (index) : nil;
                                                           }];
            [alertVc addAction:action];
        }
        [[[self class] getTopViewController] presentViewController:alertVc
                                                          animated:YES
                                                        completion:nil];
    }
}

+ (void)wb_showActionSheetWithTitle:(NSString *)title
                            message:(NSString *)message
                       clickedBlock:(WBAlertClickedBlock)clickedBlock
                 cancelActionString:(NSString *)cancelActionString
            destructiveActionString:(NSString *)destructiveActionString
                  otherActionString:(NSString *)otherActionString, ... {
    NSMutableArray *argsArray = @[].mutableCopy;
    if (cancelActionString) [argsArray addObject:cancelActionString];
    if (destructiveActionString) [argsArray addObject:destructiveActionString];
    if (otherActionString) {
        [argsArray addObject:otherActionString];
        NSString *arg;
        va_list arg_list;
        va_start(arg_list, otherActionString);
        while ((arg = va_arg(arg_list, NSString *))) {
            [argsArray addObject:arg];
        }
        va_end(arg_list);
    }
    NSAssert(argsArray.count > 0, @"请设置弹出框按钮标题");
    if ([self isiOS8OrLater]) {
        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title
                                                                         message:message
                                                                  preferredStyle:UIAlertControllerStyleActionSheet];
        for (NSInteger index = 0; index < argsArray.count; index ++) {
            UIAlertActionStyle style = UIAlertActionStyleDefault;
            if (index == 0 && cancelActionString) {
                style = UIAlertActionStyleCancel;
            }
            if (index == 1 && destructiveActionString) {
                style = UIAlertActionStyleDefault;
            }
            UIAlertAction *action = [UIAlertAction actionWithTitle:argsArray[index]
                                                             style:style
                                                           handler:^(UIAlertAction * _Nonnull action) {
                                                               clickedBlock ? clickedBlock(index) : nil;
                                                           }];
            [alertVc addAction:action];
        }
        [[[self class] getTopViewController] presentViewController:alertVc
                                                          animated:YES
                                                        completion:nil];
    }
}

+ (void)wb_showOneAlertActionWithTitle:(NSString *)title
                               message:(NSString *)message
                           actionTitle:(NSString *)actionTitle {
    [self wb_showOneAlertActionWithTitle:title
                                 message:message
                             actionTitle:actionTitle ? actionTitle : @"好的"
                             actionBlock:nil];
}

+ (void)wb_showOneAlertActionWithTitle:(NSString *)title
                               message:(NSString *)message
                           actionTitle:(NSString *)actionTitle
                          confirmBlock:(WBAlertActionBlock)confirmBlock {
    [self wb_showOneAlertActionWithTitle:title
                                 message:message
                             actionTitle:actionTitle ? actionTitle : @"好的"
                             actionBlock:confirmBlock];
}

+ (void)wb_showTwoAlertActionWithTitle:(NSString *)title
                               message:(NSString *)message
                          confirmBlock:(WBAlertActionBlock)confirmBlock {
    [self wb_showTwoAlertActionWithTitle:title
                                 message:message
                         leftActionTitle:@"取消"
                        rightActionTitle:@"确定"
                         leftActionBlock:nil
                        rightActionBlock:confirmBlock];
}

+ (void)wb_showAutoDismissAlertWithTitle:(NSString *)title
                                 message:(NSString *)message {
    [self wb_showAutoDismissAlertWithTitle:title
                                   message:message
                                afterDelay:2.f];
}

+ (void)wb_showAutoDismissActionSheetWithTitle:(NSString *)title
                                       message:(NSString *)message {
    [self wb_showAutoDismissAlertWithTitle:title
                                   message:message
                                afterDelay:2.f];
}

+ (void)wb_showCameraAuthorizationDeniedAlert {
    [self wb_showOneAlertActionWithTitle:kWBCameraDeniedMessage
                                 message:nil
                             actionTitle:nil];
}

+ (void)wb_showPhotoLibraryAuthorizationDeniedAlert {
    [self wb_showOneAlertActionWithTitle:kWBPhotoLibraryDeniedMessage
                                 message:nil
                             actionTitle:nil];
}

#pragma mark < Basic Method >
+ (void)wb_showOneAlertActionWithTitle:(NSString *)title
                               message:(NSString *)message
                           actionTitle:(NSString *)actionTitle
                           actionBlock:(WBAlertActionBlock)actionBlock {
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title
                                                                     message:message
                                                              preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *action = [UIAlertAction actionWithTitle:actionTitle
                                                     style:UIAlertActionStyleDefault
                                                   handler:^(UIAlertAction * _Nonnull action) {
                                                       actionBlock ? actionBlock() : nil;
                                                   }];
    [alertVc addAction:action];
    [[[self class] getTopViewController] presentViewController:alertVc
                                                      animated:YES
                                                    completion:nil];
}

+ (void)wb_showTwoAlertActionWithTitle:(NSString *)title
                               message:(NSString *)message
                       leftActionTitle:(NSString *)leftActionTitle
                      rightActionTitle:(NSString *)rightActionTitle
                       leftActionBlock:(WBAlertActionBlock)leftActionBlock
                      rightActionBlock:(WBAlertActionBlock)rightActionBlock {
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title
                                                                     message:message
                                                              preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *leftAction = [UIAlertAction actionWithTitle:leftActionTitle
                                                         style:UIAlertActionStyleCancel
                                                       handler:^(UIAlertAction * _Nonnull action) {
                                                           leftActionBlock ? leftActionBlock() : nil;
                                                       }];
    UIAlertAction *rightAction = [UIAlertAction actionWithTitle:rightActionTitle
                                                          style:UIAlertActionStyleDefault
                                                        handler:^(UIAlertAction * _Nonnull action) {
                                                            rightActionBlock ? rightActionBlock () : nil;
                                                        }];
    [alertVc addAction:leftAction];
    [alertVc addAction:rightAction];
    [[[self class] getTopViewController] presentViewController:alertVc
                                                      animated:YES
                                                    completion:nil];
}

+ (void)wb_showAutoDismissAlertWithTitle:(NSString *)title
                                 message:(NSString *)message
                              afterDelay:(NSTimeInterval)afterDelay {
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title
                                                                     message:message
                                                              preferredStyle:UIAlertControllerStyleAlert];
    __weak typeof(self) weakSelf = self;
    [[self getTopViewController] presentViewController:alertVc
                                              animated:YES
                                            completion:^{
                                                [weakSelf performSelector:@selector(dismiss:)
                                                               withObject:alertVc
                                                               afterDelay:afterDelay];
                                            }];
}

+ (void)wb_showAutoDismissActionSheetWithTitle:(NSString *)title
                                       message:(NSString *)message
                                    afterDelay:(NSTimeInterval)afterDelay {
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title
                                                                     message:message
                                                              preferredStyle:UIAlertControllerStyleActionSheet];
    __weak typeof(self) weakSelf = self;
    [[self getTopViewController] presentViewController:alertVc
                                              animated:YES
                                            completion:^{
                                                [weakSelf performSelector:@selector(dismiss:)
                                                               withObject:alertVc
                                                               afterDelay:afterDelay];
                                            }];
}


#pragma mark < Private Method >
+ (BOOL)isiOS8OrLater {
    return [[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0;
}

+ (void)dismiss:(UIAlertController *)alertVc {
    [alertVc dismissViewControllerAnimated:YES
                                completion:nil];
}

+ (UIViewController *)getTopViewController {
    UIViewController *result = nil;
    UIWindow * window = [[UIApplication sharedApplication] keyWindow];
    if (window.windowLevel != UIWindowLevelNormal)
    {
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(UIWindow * tmpWin in windows)
        {
            if (tmpWin.windowLevel == UIWindowLevelNormal)
            {
                window = tmpWin;
                break;
            }
        }
    }
    UIView *frontView = [[window subviews] objectAtIndex:0];
    id nextResponder = [frontView nextResponder];
    if ([nextResponder isKindOfClass:[UIViewController class]])
        result = nextResponder;
    else
        result = window.rootViewController;
    return result;
}

@end
