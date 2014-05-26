/*!CK:2585670914!*//*1398050370,178154293*/

if (self.CavalryLogger) { CavalryLogger.start_js(["JG99B"]); }

__d("PhotoBrowserDialog",["AsyncDialog","AsyncRequest","Event","Parent","cx"],function(a,b,c,d,e,f,g,h,i,j,k){function l(m){"use strict";i.listen(m.getInnerContent(),'click',function(n){var o=j.byClass(n.getTarget(),"_3w6p");if(!o)return;var p=o.getAttribute('ajaxify');if(!p)return;var q=new h().setURI(p).setRelativeTo(m.getCausalElement()).setHandler(m.hide.bind(m));g.send(q);});}e.exports=l;});
__d("legacy:control-textarea",["TextAreaControl"],function(a,b,c,d){a.TextAreaControl=b('TextAreaControl');},3);