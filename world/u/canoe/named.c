//namd.c
#include <ansi.h>

mapping surname=([
"��"    :  "zhao",         "Ǯ"    :  "qian",         
"��"    :  "sun",          "��"    :  "li",           
"��"    :  "zhou",         "��"    :  "wu",           
"֣"    :  "zhen",         "��"    :  "wang",         
"��"    :  "feng",         "��"    :  "chen",         
"��"    :  "zhu",          "��"    :  "wei",          
"��"    :  "jiang",        "��"    :  "shen",         
"��"    :  "han",          "��"    :  "yang",         
"��"    :  "zhu",          "��"    :  "qin",         
"��"    :  "you",          "��"    :  "xu",           
"��"    :  "he",           "��"    :  "lu",           
"ʩ"    :  "shi",          "��"    :  "zhang",        
"��"    :  "kong",         "��"    :  "cao",          
"��"    :  "yan",          "��"    :  "hua",          
"��"    :  "jin",          "κ"    :  "wei",          
"��"    :  "tao",          "��"    :  "jiang",        
"��"    :  "qie",          "л"    :  "xie",          
"��"    :  "zhou",         "��"    :  "yu",           
"��"    :  "bo",           "ˮ"    :  "shui",         
"�"    :  "dou",          "��"    :  "zhang",        
"��"    :  "yun",          "��"    :  "su",           
"��"    :  "pan",          "��"    :  "ge",           
"��"    :  "xi",           "��"    :  "fan",          
"��"    :  "peng",         "��"    :  "lang",         
"³"    :  "lu",           "Τ"    :  "wei",          
"��"    :  "chang",        "��"    :  "ma",           
"��"    :  "miao",         "��"    :  "feng",         
"��"    :  "hua",          "��"    :  "fang",         
"ɵ"    :  "sha",          "��"    :  "ren",          
"Ԭ"    :  "yuan",         "��"    :  "liu",          
"��"    :  "deng",         "��"    :  "bao",          
"ʷ"    :  "shi",          "��"    :  "tang",         
"��"    :  "fei",          "��"    :  "lian",         
"�"    :  "chen",         "Ѧ"    :  "xue",          
"��"    :  "lei",          "��"    :  "he",           
"��"    :  "ni",           "��"    :  "tang",         
"��"    :  "teng",         "��"    :  "yin",          
"��"    :  "luo",          "��"    :  "hua",          
"��"    :  "hao",          "��"    :  "wu",           
"��"    :  "an",           "��"    :  "chang",        
"��"    :  "le",           "��"    :  "dai",          
"ʱ"    :  "shi",          "��"    :  "fu",           
"Ƥ"    :  "pi",           "��"    :  "bian",         
"��"    :  "qi",           "��"    :  "kang",         
"��"    :  "wu",           "��"    :  "yu",           
"Ԫ"    :  "yuan",         "��"    :  "po",           
"��"    :  "gu",           "ӯ"    :  "ying",         
"ƽ"    :  "ping",         "��"    :  "huang",        
"��"    :  "he",           "��"    :  "mu",           
"Ф"    :  "xiao",         "��"    :  "yin",          
"Ҧ"    :  "yao",          "��"    :  "shao",         
"տ"    :  "zhan",         "��"    :  "wang",         
"��"    :  "qi",           "ë"    :  "mao",          
"��"    :  "yu",           "��"    :  "di",           
"��"    :  "mi",           "��"    :  "bei",          
"��"    :  "ming",         "��"    :  "zang",         
"��"    :  "ji",           "��"    :  "fu",           
"��"    :  "cheng",        "��"    :  "dai",          
"̸"    :  "tan",          "��"    :  "song",         
"é"    :  "mao",          "��"    :  "pang",         
"��"    :  "xiong",        "��"    :  "ji",           
"��"    :  "su",           "��"    :  "qu",           
"��"    :  "xiang",        "ף"    :  "zhu",          
"��"    :  "dong",         "��"    :  "liang",        
"��"    :  "fan",          "��"    :  "hu",           
"��"    :  "ling",         "��"    :  "ho",           
"��"    :  "yu",           "��"    :  "wan",          
"֧"    :  "zhi",          "��"    :  "ke",           
"��"    :  "jiu",          "��"    :  "guan",         
"¬"    :  "lu",           "Ӣ"    :  "ying",         
"��"    :  "qiu",          "��"    :  "hou",          
"��"    :  "yue",          "˧"    :  "suai",         
"˾��"  :  "sima",         "�Ϲ�"  :  "shangguan",    
"ŷ��"  :  "ouyang",       "�ĺ�"  :  "xiahou",       
"���"  :  "zhuge",        "����"  :  "wenren",       
"����"  :  "dongfang",     "����"  :  "helian",       
"�ʸ�"  :  "huangpu",      "ξ��"  :  "yuchi",       
"����"  :  "gongyang",     "�̨"  :  "zhantai",      
"����"  :  "gongye",       "����"  :  "zongzheng",    
"���"  :  "puyang",       "����"  :  "chunyu",       
"����"  :  "shanyu",       "߳Ǭ"  :  "chigan",       
"����"  :  "shentu",       "����"  :  "gongsun",     
"����"  :  "zhongsun",     "ԯ��"  :  "xuanyuan",     
"���"  :  "linghu",       "����"  :  "zhongli",      
"����"  :  "yuwen",        "����"  :  "zhangsun",    
"Ļ��"  :  "murong",       "˾ͽ"  :  "situ",         
"ʦ��"  :  "shikong",      "��"  :  "zhuankong",    
"��ľ"  :  "duanmu",       "����"  :  "wuma",         
"����"  :  "gongxi",       "���"  :  "qidiao",       
"����"  :  "lezheng",      "����"  :  "xiangsi",      
"����"  :  "gongliang",    "��ֺ"  :  "tuozhi",       
"�й�"  :  "jiagu",        "�׸�"  :  "zaifu",        
"����"  :  "guliang",      "����"  :  "chujing",      
"����"  :  "dugu",        "��۳"  :  "ruye",         
"Ϳ��"  :  "tuqin",        "��ǧ"  :  "duanqian",     
"����"  :  "baili",        "����"  :  "dongguo",      
"�Ϲ�"  :  "nanguo",       "����"  :  "huyan",        
"�麣"  :  "guihai",       "����"  :  "yangshe",      
"΢��"  :  "weisheng",     "����"  :  "liangqiu",     
"����"  :  "zuoqiu",       "����"  :  "dongmen",      
"����"  :  "ximen",        "����"  :  "baishang",     
"�Ϲ�"  :  "nangong",      "��"    :  "gou",          
"��"    :  "kang",         "��"    :  "kuang",        
"��"    :  "hou",          "��"    :  "you",          
"��"    :  "qing",         "��"    :  "shang",        
"Ĳ"    :  "mo",           "��"    :  "she",          
"��"    :  "er",           "ī"    :  "mo",           
"��"    :  "ha",           "��"    :  "qiao",         
"��"    :  "nian",         "��"    :  "ai",           
"��"    :  "yang",         "١"    :  "dong",         
"��"    :  "di",           "��"    :  "wu",           
"��"    :  "yan",          "��"    :  "fu",           
"��"    :  "kai",          "��"    :  "zong",         
"��"    :  "zong",         "��"    :  "lin",          
"ʯ"    :  "shi",
]);

mapping jp_surname=([
"ɽ��"  :  "shanben",      "����"  :  "guitian",      
"����"  :  "zisan",        "��"  :  "dadao",        
"����"  :  "songxia",      "����"  :  "hengtian",     
"��֥"  :  "dongzhi",      "��"  :  "houben",       
"��Ұ"  :  "chuangye",     "ɽ��"  :  "shankou",      
"��ľ"  :  "lingmu",       "�ڲ�"  :  "gangcang",     
"С��"  :  "xiaodao",      "����"  :  "jinshang",     
"����"  :  "annai",        "ǳ��"  :  "qiantian",     
"����"  :  "zuoteng",      "��ĩ"  :  "guangmu",      
"����"  :  "dazhu",        "���"  :  "dachun",       
"����"  :  "bozuo",        "����"  :  "fugang",       
"����"  :  "dongxiang",
]);

mapping middle_name=([
"��" : "zhong",		"Т" : "xiao",
"��" : "li",		"��" : "yi",
"��" : "zhi",		"��" : "bu",
"��" : "ren",		"��" : "kuang",
"��" : "xian",		"��" : "ling",
"��" : "fu",		"��" : "nai",
"��" : "da",		"С" : "xiao",
"��" : "xiao",		"��" : "gao",
"��" : "ke",		"��" : "a",
"��" : "jin",		"��" : "shi",
"��" : "ke",		"��" : "shu",
"֮" : "zhi",		"��" : "fei",
"��" : "fu",		"ʱ" : "shi",
"��" : "ruo",		"��" : "qing",
"��" : "wen",		"��" : "wu",
"��" : "duo",		"��" : "cai",
"��" : "zhang",		"��" : "zi",
"��" : "yong",		"��" : "you",
"��" : "jiu",		"��" : "ren",
"Ϊ" : "weo",		"һ" : "yi",
]);

mapping male_name=([
"��" : "ba",		"��" : "bai",
"��" : "ban",		"��" : "bin",
"��" : "bin",		"��" : "chang",
"��" : "chao",		"��" : "cheng",
"��" : "chuan",		"��" : "ding",
"��" : "ding",		"��" : "fa",
"��" : "fei",		"��" : "feng",
"��" : "feng",		"��" : "gan",
"�" : "gan",		"��" : "gui",
"��" : "guang",		"��" : "hai",
"��" : "hu",		"��" : "hua",
"��" : "hao",		"��" : "hong",
"��" : "ji",		"��" : "jian",
"��" : "jian",		"��" : "jian",
"��" : "jiang",		"��" : "jin",
"��" : "jie",		"��" : "jun",
"��" : "kan",		"��" : "liang",
"��" : "qi",		"��" : "min",
"��" : "ming",		"��" : "ming",
"��" : "ning",		"��" : "pei",
"��" : "qi",		"ǿ" : "qiang",
"��" : "rong",		"ɽ" : "shan",
"̩" : "tai",		"��" : "tao",
"ͦ" : "ting",		"ΰ" : "wei",
"��" : "xi",		"��" : "xiang",
"��" : "xiong",		"��" : "xu",
"��" : "dou",		"��" : "yi",
"�" : "yu",		"��" : "yu",
"��" : "yu",		"��" : "yue",
"��" : "zhou",		
]);
			
mapping female_name=([
"��" : "ai",		"��" : "chun",
"��" : "dan",		"��" : "fang",
"��" : "fen",		"��" : "feng",
"��" : "gu",		"��" : "hong",
"��" : "hong",		"��" : "jiao",
"��" : "juan",		"��" : "ju",
"��" : "lan",		"�" : "lan",
"��" : "li",		"��" : "li",
"��" : "lian",		"��" : "ling",
"��" : "lin",		"��" : "na",
"��" : "qin",		"��" : "qin",
"ٻ" : "qian",		"Ƽ" : "ping",
"��" : "ding",		"ϼ" : "xia",
"��" : "xiang",		"��" : "er",
"��" : "yan",		"Ӣ" : "ying",
"��" : "ying",		"��" : "yu",
"��" : "zhen",		"��" : "zhu",
]);
	
mapping jp_name=([
"̫��"   : "tailang",		"����"   : "cilang",
"����"   : "sanlang",		"����"   : "silang",
"����"   : "wulang",		"ʮһ��" : "shiyilang",
"ʮ����" : "shisilang",		"��ʮ��" : "ershiliu",
"����"   : "junshu",		"����"   : "ningci",
"Ӣ��"   : "yingji",		"ұ��"   : "zhizi",
"����"   : "junxiong",		"����"   : "mufu",
"���"   : "guangfu",		"��һ"   : "jingyi",
"Ӣ��"   : "yingshi",		"��ʯ"   : "shushi",
"�弪"   : "yuji",		"һҶ"   : "yiye",
"�ӹ�"   : "zigui",		"����"   : "daozhao",
"����"   : "yichong",		"��԰"   : "songyuan",
"��ˮ"   : "shenshui",		"���"   : "daguan",
"���"   : "fengguo",		"Т��"   : "xiaohe",
"ï"     : "mao",		"��"     : "chuan",
"��"     : "wei",		"����"   : "daoshou",
"����"   : "guangyun",		"����"   : "anzhi",
"ɽ��"   : "shanle",		"�ζ�"   : "menger",
]);

mapping color_list = ([
"��":	"chi",		"��":	"hong",
"��":	"huang",	"��":	"lu",
"��":	"qing",		"��":	"lan",
"��":	"zi",		"��":	"wu",
"��":	"hei",		"��":	"yin",
"��":	"bai",		"��":	"jin",
"��":	"hui",		"ľ":	"mu",
"ˮ":	"shui",		"��":	"huo",
"��":	"tu",		"θ":	"wei",
"��":	"gui",		"��":	"yue",
"��":	"zhu",		"��":	"ri",
"��":	"dou",		"��":	"zui",
"��":	"kui",		"��":	"shen"
]);

mapping animal_list =([
"��":	"tu",		"��":	"hu",
"��":	"long",		"��":	"jiao",
"��":	"hu",		"��":	"bao",
"��":	"ma",		"¹":	"lu",
"��":	"yang",		"��":	"she",
"�":	"zhang",	"��":	"ji",
"��":	"gou",		"��":	"lang",
"Գ":	"yuan",		"��":	"hou",
"��":	"shu",		"ţ":	"niu",
"��":	"zhu",		"��":	"fu",
"��":	"chai",		"̡":	"lai",
"��":	"fei",		"��":	"mang",
"��":	"xiong",	"��":	"xiang",
"��":	"diao",		"��":	"li",
"�":	"huan",		"�":	"pi",
"��":	"yan",		"�":	"yin",
"��":	"zhi",		"��":	"pao",
"�":	"ni",		"��":	"ao",
"��":	"ling",		"��":	"ji",
"��":	"xing",
]);

mapping animal_names = ([
"����":"huli",		"����":"heixiong",
"����":"gouxiong",	"����":"baixiong",
"Ы��":"xiezi",		"���":"chanchu",
"���":"wugong",	"����":"tubie",
"�ɻ�":"feihuang",	"�ȳ�":"huangchong",
"�����":"daqingchong",	"����":"chouchong",
"����":"tiaozao",	"ʭ��":"shizi",
"�ϻ�":"laohu",		"ʨ��":"shizi",
"��ʨ":"huangshi",	"��ʨ":"heishi",
"��ʨ":"baishi",	"Ұ��":"yetu",
"����":"huabao",	"ɽ��":"shanbao",
"�ݱ�":"caobao",	"ɽ��":"shanyang",
"���":"mahou",		"⨺�":"mihou",
"Գ��":"yuanhou",	"����":"huilang",
"Ұ��":"yezhu",		"֩��":"zhizhu",
"��¹":"malu",		"��¹":"bailu",
"��¹":"huilu",		"��¹":"heilu",
"ɽ��":"shanji",	"Ұ��":"yeji",
"����":"zhiji",		"���":"ciwei",
"������":"huahuli",	"�׺���":"baihuli",
"�Һ���":"huihuli",	"����":"xingxing",
"����":"feifei",	"����":"baima",
"����":"hongma",	"����":"heima",
"��è":"baimao",	"��è":"huamao",
"��è":"heimao",	"Ұè":"yemao",
"Ұ��":"yema",		"Ұ¿":"yelu",
"����":"baitu",		"����":"huitu",
"ˮţ":"shuiniu",	"��ţ":"maoniu",
"Ұţ":"yeniu",		"����":"baishu",
"����":"huishu",	"������":"heimayi",
"����":"mayi",		"����":"baiyi",
"ɽ����":"shanlaoshu",	"����":"huashe",
"����":"qingshe",	"����":"baishe",
"�Ұ���":"huibanshe",	"����":"jumang",
"ˮ��":"shuishe",	"����":"haili",
"����":"heli",
]);

mapping middle_list =([
"��"	:	"jiao",		"ͷ"	:	"tou",
"β"	:	"wei",		"��"	:	"zui",
"��"	:	"er",		"��"	:	"yan",
"��"	:	"bi",		"��"	:	"ya",
"��"	:	"she",		"��"	:	"shen",
"צ"	:	"zhua",
]);
string *title_list = ({ 
	"�¹���ͽ",	"�������ѽ�", 
	"��ѩɽ����",	"�޵׶�����",
	"����ɽ��ͽ",	"��ׯ����ͽ", 
	"�ظ�ԩ��",	"������ͽ",
	"�칬�ѽ�",	"��������",
	"�޵׶�С��",	"��ׯ�۶�ͽ",
	"���Ӷ�ɮ",
});	

varargs mapping random_name(string type)
{
	mapping name;
	int a,b,c;
	string *surnames, *middle_names, *last_names;
	string temp_name, *temp_id, long;
	
	name=allocate_mapping(3);
	
	switch(type)
	{
		case "male" :
		surnames=keys(surname);
		middle_names=keys(middle_name);
		last_names=keys(male_name);
		a=random(sizeof(surnames));
		b=random(sizeof(middle_names));
		c=random(sizeof(last_names));
		if(random(100)>20)
		{
			temp_name=surnames[a]
				 + middle_names[b]
				 + last_names[c];
			temp_id=({surname[surnames[a]]+" "
				   +middle_name[middle_names[b]]
				   +male_name[last_names[c]],
				   surname[surnames[a]]});
		}
		else {
			temp_name=surnames[a]
				 + last_names[c];
			temp_id=({surname[surnames[a]]+" "
				   +male_name[last_names[c]],
				   surname[surnames[a]]});
		}
		if(random(2)==0)
			long=HIM"��������"NOR;
		if(random(2)==1)
			long=HIG"������������"NOR;
        if(random(2)==2)
			long=HIC"���⸮����"NOR;
		name=([
			"name" : temp_name,
			"id"   : temp_id,
//			"title": YEL"����"NOR,
            "title"   : long,
		]);
		break;
		case "female" :
		surnames=keys(surname);
		middle_names=keys(middle_name);
		last_names=keys(female_name);
		a=random(sizeof(surnames));
		b=random(sizeof(middle_names));
		c=random(sizeof(last_names));
		if(random(100)>20)
		{
			temp_name=surnames[a]
				 + middle_names[b]
				 + last_names[c];
			temp_id=({surname[surnames[a]]+" "
				   +middle_name[middle_names[b]]
				   +female_name[last_names[c]],
				   surname[surnames[a]]});
		}
		else {
			temp_name=surnames[a]
				 + last_names[c];
			temp_id=({surname[surnames[a]]+" "
				   +female_name[last_names[c]],
				   surname[surnames[a]]});
		}
		if(random(2)==0)
			long=HIM"���ݳǸ��"NOR;
		if(random(2)==1)
			long=HIG"�������輧"NOR;
        if(random(2)==2)
			long=HIC"���⸮��Ů"NOR;
		name=([
			"name" : temp_name,
			"id"   : temp_id,
//			"title": HIM"��������Ů"NOR,
            "title"   : long,
		]);
		break;
		case "japan" :
		surnames=keys(jp_surname);
		last_names=keys(jp_name);
		a=random(sizeof(surnames));
		b=random(sizeof(last_names));
		name=([
			"name" : surnames[a]
				 + last_names[b],
			"id"   : ({jp_surname[surnames[a]]+" "
				   +jp_name[last_names[b]],
				   jp_surname[surnames[a]]}),
			"title": WHT"�ձ���ʿ"NOR,
		]);
		break;
                case "yaoguai":
		if(random(2))
		{
			surnames=keys(animal_list);
			middle_names=keys(middle_list);
			a=random(sizeof(surnames));
			b=random(sizeof(middle_names));
			c=random(sizeof(surnames));
			name=([
				"name" 	: surnames[a]+
					  middle_names[b]+
					  surnames[c],
				"id"	: ({animal_list[surnames[a]]+
					    middle_list[middle_names[b]]+" "+
					    animal_list[surnames[c]],
					    animal_list[surnames[c]]}),
                                "title"	:title_list[random(sizeof(title_list))],
			]);
		}
		else
		{
			if(random(2))
			{
				surnames=keys(color_list);
				middle_names=keys(animal_list);
				a=random(sizeof(surnames));
				b=random(sizeof(middle_names));
				c=random(2);
				temp_name=surnames[a]+
					  middle_names[b];
				temp_name+=c?"��":"��";
				if(c)
					temp_id=({color_list[surnames[a]]+
						  animal_list[middle_names[b]]+" "+
					  	"jing", "jing"});
				else
					temp_id=({color_list[surnames[a]]+
						  animal_list[middle_names[b]]+" "+
					  	"guai",	"guai"});
			}
			else
			{
				surnames=keys(animal_names);
				a=random(sizeof(surnames));
				b=random(2);
				temp_name=surnames[a];
				temp_name+=b?"��":"��";
				if(b)
					temp_id=({animal_names[surnames[a]]+" "+
						  "jing", "jing"});
				else
					temp_id=({animal_names[surnames[a]]+" "+
						  "guai", "guai"});
			}
			name=([
				"name" : temp_name,
				"id"   : temp_id,
				"title": "NONE",
			]);
		}
		break;
		default:
		name=([
			"name" : "����",
			"id"   : ({"test"}),
		]);
		break;
	}
	return name;
}
