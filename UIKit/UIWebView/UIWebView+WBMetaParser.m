//
//  UIWebView+WBMetaParser.m
//  WBCategories
//
//  Created by Admin on 2018/2/11.
//  Copyright © 2018年 WENBO. All rights reserved.
//

#import "UIWebView+WBMetaParser.h"

@implementation UIWebView (WBMetaParser)

- (NSArray *)wb_getMetaData {
    NSString *string = [self stringByEvaluatingJavaScriptFromString:@""
                        "var json = '[';                                    "
                        "var a = document.getElementsByTagName('meta');     "
                        "for(var i=0;i<a.length;i++){                       "
                        "   json += '{';                                    "
                        "   var b = a[i].attributes;                        "
                        "   for(var j=0;j<b.length;j++){                    "
                        "       var name = b[j].name;                       "
                        "       var value = b[j].value;                     "
                        "                                                   "
                        "       json += '\"'+name+'\":';                    "
                        "       json += '\"'+value+'\"';                    "
                        "       if(b.length>j+1){                           "
                        "           json += ',';                            "
                        "       }                                           "
                        "   }                                               "
                        "   json += '}';                                    "
                        "   if(a.length>i+1){                               "
                        "       json += ',';                                "
                        "   }                                               "
                        "}                                                  "
                        "json += ']';                                       "];
    
    NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
    NSError*   error = nil;
    id array = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
    if(array==nil) NSLog(@"An error occured in meta parser.");
    return array;
}

@end