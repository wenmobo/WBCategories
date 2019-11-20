//
//  WB_MacroDefinition.h
//  WB_MacroDefinition
//
//  Created by Admin on 2017/8/9.
//  Copyright © 2017年 Admin. All rights reserved.
//

#ifndef WB_MacroDefinition_h
#define WB_MacroDefinition_h

#import "NSString+WBAddtional.h"

/**  < 自定义高效率log >  */
#ifdef DEBUG
#   define NSLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#   define NSLog(...)
#endif

// MARK: --------ABOUT SCREEN & SIZE 屏幕&尺寸
/**
 iPad Air {{0, 0}, {768, 1024}}
 iphone4s {{0, 0}, {320, 480}}               960*640
 iphone5 5s {{0, 0}, {320, 568}}             1136*640
 iphone6 6s {{0, 0}, {375, 667}}             1334*750
 iphone6Plus 6sPlus {{0, 0}, {414, 736}}     1920*1080
 iPhone X {375, 812}                         1125*2436
 Apple Watch 1.65inches(英寸)                 320*640
 */
/**  < 需要横屏或者竖屏，获取屏幕宽度与高度 当前Xcode支持iOS8及以上 >  */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
#define WB_SCREEN_WIDTH ([[UIScreen mainScreen] respondsToSelector:@selector(nativeBounds)]?[UIScreen mainScreen].nativeBounds.size.width/[UIScreen mainScreen].nativeScale:[UIScreen mainScreen].bounds.size.width)
#define WB_SCREEN_HEIGHT ([[UIScreen mainScreen] respondsToSelector:@selector(nativeBounds)]?[UIScreen mainScreen].nativeBounds.size.height/[UIScreen mainScreen].nativeScale:[UIScreen mainScreen].bounds.size.height)
#define WB_SCREEN_SIZE ([[UIScreen mainScreen] respondsToSelector:@selector(nativeBounds)]?CGSizeMake([UIScreen mainScreen].nativeBounds.size.width/[UIScreen mainScreen].nativeScale,[UIScreen mainScreen].nativeBounds.size.height/[UIScreen mainScreen].nativeScale):[UIScreen mainScreen].bounds.size)
#else
#define WB_SCREEN_WIDTH [UIScreen mainScreen].bounds.size.width
#define WB_SCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height
#define WB_SCREEN_SIZE [UIScreen mainScreen].bounds.size
#endif

#define SCREEN_BOUNDS [UIScreen mainScreen].bounds

// MARK:--------适配宏定义
/**  < Adaptive  >  */
#define WB_AdjustsScrollViewInsets_NO(scrollView,vc)\
do { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
if ([UIScrollView instancesRespondToSelector:NSSelectorFromString(@"setContentInsetAdjustmentBehavior:")]) {\
[scrollView   performSelector:NSSelectorFromString(@"setContentInsetAdjustmentBehavior:") withObject:@(2)];\
} else {\
vc.automaticallyAdjustsScrollViewInsets = NO;\
}\
_Pragma("clang diagnostic pop") \
} while (0)

#define  WB_AdjustsScrollViewInsets(scrollView)\
do {\
_Pragma("clang diagnostic push")\
_Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"")\
if ([scrollView respondsToSelector:NSSelectorFromString(@"setContentInsetAdjustmentBehavior:")]) {\
NSMethodSignature *signature = [UIScrollView instanceMethodSignatureForSelector:@selector(setContentInsetAdjustmentBehavior:)];\
NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:signature];\
NSInteger argument = 2;\
invocation.target = scrollView;\
invocation.selector = @selector(setContentInsetAdjustmentBehavior:);\
[invocation setArgument:&argument atIndex:2];\
[invocation retainArguments];\
[invocation invoke];\
}\
_Pragma("clang diagnostic pop")\
} while (0)

/**  < 屏幕适配 ipone6/6s 控件宽高 字体大小都可以用这个宏 >  */
#define WB_AUTOLAYOUTSIZE(size) ((size) * (WB_SCREEN_WIDTH / 375))

#define WB_VIEWSAFEAREAINSETS(view) ({UIEdgeInsets i; if(@available(iOS 11.0, *)) {i = view.safeAreaInsets;} else {i = UIEdgeInsetsZero;} i;})

///屏幕像素
#define WB_SCREEN_SCALE [UIScreen mainScreen].scale

// MARK: --------设备&系统判断
/**  < 判断当前的iPhone设备 >  */
#define WB_IS_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
//#define IS_IPHONE ([[[UIDevice currentDevice] model] isEqualToString:@"iPhone"])

/**  < 判断是否为iPad >  */
#define WB_IS_IPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
//#define IS_IPAD ([[[UIDevice currentDevice] model] isEqualToString:@"iPad"])

/**  < 判断是否为ipod >  */
#define WB_IS_IPOD ([[[UIDevice currentDevice] model] isEqualToString:@"iPod touch"])

/**  < 判断iPhone 4/iPhone 4S 像素640x960，@2x >  */
#define WB_IS_IPHONE4_OR_4S [[UIScreen mainScreen] bounds].size.width == 320.0f && [[UIScreen mainScreen] bounds].size.height == 480.0f
//#define iPhone4 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) : NO)

/**  < 判断是否为 iPhone5/SE/iPhone5S/iPhone5C 分辨率320x568，像素640x1136，@2x >  */
#define WB_IS_IPHONE5_OR_SE [[UIScreen mainScreen] bounds].size.width == 320.0f && [[UIScreen mainScreen] bounds].size.height == 568.0f

/**  < 判断是否为iPhone 6/6s 分辨率375x667，像素750x1334，@2x >  */
#define WB_IS_IPHONE6_OR_6S [[UIScreen mainScreen] bounds].size.width == 375.0f && [[UIScreen mainScreen] bounds].size.height == 667.0f

/**  < 判断是否为iPhone 6Plus/6sPlus 分辨率414x736，像素1242x2208，@3x >  */
#define WB_IS_IPHONE6PLUS_OR_6SPLUS [[UIScreen mainScreen] bounds].size.width == 414.0f && [[UIScreen mainScreen] bounds].size.height == 736.0f

/**  < 判断是否是iPhone X >  */
#define WB_IS_iPHoneX \
({BOOL isPhoneX = NO;\
if (@available(iOS 11.0, *)) {\
isPhoneX = [[UIApplication sharedApplication] delegate].window.safeAreaInsets.bottom > 0.0;\
}\
(isPhoneX);})

/**  < 获取系统版本 >  */
#define WB_IOS_SYSTEM_VERSION [[[UIDevice currentDevice] systemVersion] floatValue]

/**  < 系统版本判断 >  */
#define WB_SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define WB_SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define WB_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define WB_SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define WB_SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

/**  < 判断 iOS 8 或更高的系统版本 >  */
#define WB_SYSTEM_VERSION_8_OR_LATER WB_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"8.0")
//#define kWB_SYSTEM_VERSION_8_OR_LATER (([[[UIDevice currentDevice] systemVersion] floatValue] >=8.0)? (YES):(NO))

/**  < 判断 iOS 9 或更高的系统版本 >  */
#define WB_SYSTEM_VERSION_9_OR_LATER WB_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"9.0")
//#define kWB_SYSTEM_VERSION_9_OR_LATER (([[[UIDevice currentDevice] systemVersion] floatValue] >=9.0)? (YES):(NO))

/**  < 判断 iOS 11 或更高的系统版本 >  */
#define WB_SYSTEM_VERSION_11_OR_LATER WB_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"11.0")

/**  < 导航栏高度 无largeTitle >  */
#define WB_NAVIGATIONBAR_HEIGHT 44
/**  < 状态栏高度 >  */
#define WB_STATUSBAR_HEIGHT [UIApplication sharedApplication].statusBarFrame.size.height
/**  < 整个导航栏高度 >  */
#define WB_NAVI_HEIGHT (kWB_IS_IPHONE_X ? (88) : (64))
/**  < 标签栏高度 >  */
#define WB_TABBAR_HEIGHT (kWB_IS_IPHONE_X ? (83) : (49))
/**  < iOS 11 底部安全域距离 >  */
#define kWB_BOTTOM_SAFEAREA_HEIGHT (kWB_IS_IPHONE_X ? (34) : (0))

// MARK: --------颜色相关
/**  < 随机色 >  */
#define WB_RANDOM_COLOR [UIColor colorWithRed:arc4random_uniform(256)/255.0 green:arc4random_uniform(256)/255.0 blue:arc4random_uniform(256)/255.0 alpha:1.0]
/**  < 透明色 >  */
#define WB_CLEAR_COLOR [UIColor clearColor]
/**  < RGB颜色 >  */
#define WB_RGB_COLOR(r, g, b) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:1.0]
/**  < RGBA颜色 >  */
#define WB_RGBA_COLOR(r, g, b, a) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:a]
/**  < HEX Color >  */
#define WB_COLORFROMHEXRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

// MARK: --------系统单例
/**  < 通知中心 >  */
#define WB_NOTIFICATIONCENTER [NSNotificationCenter defaultCenter]
/**  < 系统偏好设置 >  */
#define WB_NSUSERDEFAULTS [NSUserDefaults standardUserDefaults]

/**  < 强弱引用 >  */
#define WB_WEAKSELF(type) __weak typeof(type) weak##type = type;
#define WB_STRONGSELF(type) __strong typeof(type) type = weak##type;

// MARK: -------解决循环引用
#define WBWeakObjc(o) autoreleasepool{} __weak typeof(o) o##Weak = o;
#define WBStrongObjc(o) autoreleasepool{} __strong typeof(o) o = o##Weak;

#ifndef weakify
    #if DEBUG
        #if __has_feature(objc_arc)
        #define weakify(object) autoreleasepool{} __weak __typeof__(object) weak##_##object = object;
        #else
        #define weakify(object) autoreleasepool{} __block __typeof__(object) block##_##object = object;
        #endif
    #else
        #if __has_feature(objc_arc)
        #define weakify(object) try{} @finally{} {} __weak __typeof__(object) weak##_##object = object;
        #else
        #define weakify(object) try{} @finally{} {} __block __typeof__(object) block##_##object = object;
        #endif
    #endif
#endif

#ifndef strongify
    #if DEBUG
        #if __has_feature(objc_arc)
        #define strongify(object) autoreleasepool{} __typeof__(object) object = weak##_##object;
        #else
        #define strongify(object) autoreleasepool{} __typeof__(object) object = block##_##object;
        #endif
    #else
        #if __has_feature(objc_arc)
        #define strongify(object) try{} @finally{} __typeof__(object) object = weak##_##object;
        #else
        #define strongify(object) try{} @finally{} __typeof__(object) object = block##_##object;
        #endif
    #endif
#endif

/**  < 程序管理代理 >  */
#define WB_APPLICATIONDELEGATE ((AppDelegate *)[UIApplication sharedApplication].delegate)
/**  < 主窗口 >  */
#define WB_KEYWINDOW [UIApplication sharedApplication].keyWindow
/**  < 添加视图到主窗口 >  */
#define WB_ADDVIEWTOKEYWINDOW(view) [kWB_KEYWINDOW addSubview:view]
/**  < 协议窗口 >  */
#define WB_APPDELEGATEWINDOW [[UIApplication sharedApplication].delegate window]

// MARK: --------加载图片
/**  < 通过文件路径获取图片 文件夹 >  */
#define WB_IMAGEWITHFILE(imageFile) [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForAuxiliaryExecutable:imageFile]]
/**  < 通过图片名获取图片 Assets >  */
#define WB_IMAGEWITHNAME(imageName) [UIImage imageNamed:imageName]

/**  < 由角度转换弧度 >  */
#define WB_DEGREESTORADIAN(x) (M_PI * (x) / 180.0)
/**  < 由弧度转换角度 >  */
#define WB_RADIANTODEGREES(radian) (radian*180.0)/(M_PI)

/**  < 获取当前语言 >  */
#define WB_CURRENTLANGUAGE [[NSLocale preferredLanguages] firstObject]

// MARK: --------沙盒路径获取
/**  < 获取沙盒 Document >  */
#define WB_DOCUMENT_PATH [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]
/**  < 获取沙盒 Cache >  */
#define WB_CACHE_PATH [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject]

// MARK: --------同步锁
#define WB_LOCK(lock) dispatch_semaphore_wait(lock, DISPATCH_TIME_FOREVER);
#define WB_UNLOCK(lock) dispatch_semaphore_signal(lock);

// MARK: --------多线程
/** < 主线程安全执行 >  */
#ifndef dispatch_main_async_safe
#define dispatch_main_async_safe(block) dispatch_queue_async_safe(dispatch_get_main_queue(), block)
#endif

/** < 子线程安全执行 >  */
#ifndef dispatch_queue_async_safe
#define dispatch_queue_async_safe(queue, block)\
if (dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL) == dispatch_queue_get_label(queue)) {\
block();\
} else {\
dispatch_async(queue, block);\
}
#endif

// MARK: --------INLINE函数
CG_INLINE CGRect
WBCGRectMakeWithSize(CGSize size) {
    return CGRectMake(0, 0, size.width, size.height);
}

/// 判断一个 CGSize 是否为空（宽或高为0）
CG_INLINE BOOL
WBCGSizeIsEmpty(CGSize size) {
    return size.width <= 0 || size.height <= 0;
}

/**
*  某些地方可能会将 CGFLOAT_MIN 作为一个数值参与计算（但其实 CGFLOAT_MIN 更应该被视为一个标志位而不是数值），可能导致一些精度问题，所以提供这个方法快速将 CGFLOAT_MIN 转换为 0
*  issue: https://github.com/Tencent/QMUI_iOS/issues/203
*/
CG_INLINE CGFloat wb_removeFloatMin(CGFloat floatValue) {
    return floatValue == CGFLOAT_MIN ? 0 : floatValue;
}

/**
*  基于指定的倍数，对传进来的 floatValue 进行像素取整。若指定倍数为0，则表示以当前设备的屏幕倍数为准。
*
*  例如传进来 “2.1”，在 2x 倍数下会返回 2.5（0.5pt 对应 1px），在 3x 倍数下会返回 2.333（0.333pt 对应 1px）。
*/
CG_INLINE CGFloat wb_flatSpecificScale(CGFloat floatValue, CGFloat scale) {
    floatValue = wb_removeFloatMin(floatValue);
    scale = scale ?: [UIScreen mainScreen].scale;
    CGFloat flattedValue = ceil(floatValue * scale) / scale;
    return flattedValue;
}

/**
*  基于当前设备的屏幕倍数，对传进来的 floatValue 进行像素取整。
*
*  注意如果在 Core Graphic 绘图里使用时，要注意当前画布的倍数是否和设备屏幕倍数一致，若不一致，不可使用 flat() 函数，而应该用 flatSpecificScale
*/

CG_INLINE CGFloat wb_flat(CGFloat floatValue) {
    return wb_flatSpecificScale(floatValue, 0);
}

#pragma mark - Selector
/**
 根据给定的 getter selector 获取对应的 setter selector
 @param getter 目标 getter selector
 @return 对应的 setter selector
 */
CG_INLINE SEL
wb_setterWithGetter(SEL getter) {
    NSString *getterString = NSStringFromSelector(getter);
    NSMutableString *setterString = [[NSMutableString alloc] initWithString:@"set"];
    [setterString appendString:getterString.wb_capitalizedString];
    [setterString appendString:@":"];
    SEL setter = NSSelectorFromString(setterString);
    return setter;
}

#endif /* WB_MacroDefinition_h */

