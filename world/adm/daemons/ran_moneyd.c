

#include <ansi.h>

int move_money(int amount);
int write_money_log(object room,int amount,string room_s);
int get_number();
int get_write_number();
void write_log(object room_o,string number,string room_s);
int del_log(string x);





int move_money(int amount)
{

	string mvdir,*dir,room_s;
	int f;
	object room_o;
        string *path = ({
           "/d/changan/",            "/d/sea/",               "/d/death/",
           "/d/eastway/",            "/d/westway/",           "/d/city/",
           "/d/nanhai/",             "/d/kaifeng/",           "/d/lingtai/",  
		   "/d/moon/",              "/d/ourhome/honglou/",
           "/d/death/",              "/d/qujing/baoxiang/",   "/d/qujing/biqiu/",
           "/d/qujing/chechi/",      "/d/qujing/fengxian/",   "/d/qujing/jindou/",
           "/d/qujing/jinping/",     "/d/qujing/jisaiguo/",   "/d/qujing/nuerguo/",
           "/d/qujing/pansi/",       "/d/qujing/tongtian/",   "/d/qujing/qilin/",
           "/d/qujing/qinfa/",       "/d/qujing/tianzhu/",    "/d/qujing/wuji/",
           "/d/qujing/yuhua/",       "/d/qujing/zhujie/",     "/d/qujing/zhuzi/",

           });
  
	mvdir=path[random(sizeof(path))];
	dir=get_dir(mvdir);

	room_s=dir[random(sizeof(dir))];
	room_s=mvdir+room_s;
	room_o=find_object(room_s);
	if(!room_o) room_o=load_object(room_s);
	if(!room_o) return 0;

		amount>0 ?f=amount:f=2000+random(4001);
	write_money_log(room_o,f,room_s);

	return 1;
}

int write_money_log(object room,int amount,string room_s)
{
	int i,x;
        if(random(100)<=10) {
                //message_job(HIR"\n财神爷突然降临人间，把地上的财宝全收走了……\n\n"NOR);
				message( "chat", HIR"\n财神爷突然降临人间，把地上的财宝全收走了……\n\n"NOR, users() );
		rm("/u/yekai/caishen/money");
		return 0;
	}
	if((i=get_number())>=20) return 0;
	if(!(x=get_write_number())) return 0;
	room->set( "dig_money/value",amount);
	room->set( "dig_money/number",x);
	write_log(room,""+x+"",room_s);
}

int get_number()
{
	string msg,*line;
	int i,x=0;
	if(!(msg=read_file("/u/yekai/caishen/money"))) return 0;
	line=explode(msg,"\n");
	for(i=0;i<sizeof(line);i++) {
		if(line[i]=="") continue;
		if(strlen(line[i])>2 || to_int(line[i])>20 || to_int(line[i])<1 ) continue;
		x++;
	}
	return x;
}

int get_write_number()
{
	int i,x,k,*ar=({});
	string msg,*line;
	if(!(msg=read_file("/u/yekai/caishen/money"))) return 1;
	line=explode(msg,"\n");
	for(x=0;x<sizeof(line);x++) {
		if(line[x]=="") continue;
		if(strlen(line[i])>2 || (k=to_int(line[x]))>20 || k<1 ) continue;
		ar+=({k});
	}
	for(i=1;i<=20;i++)
		if(member_array(i,ar)==-1) return i;
	return 0;
}

void write_log(object room_o,string number,string room_s)
{
	string r_long;
	int j,k;
	r_long=room_o->query("long");
	j=strlen(r_long);
	//往房间描述里面加一些“□”，使找的工作变得难些。
	for(int x=0;x<j;x+=2) {
		if(r_long[x]<=160 || r_long[x]>=255 ) {
			x--;
			continue;
		}
                if(random(10)<4) {
			k=x+1;
			r_long=replace_string(r_long,r_long[x..k],"□");
		}
	}
	
	write_file("/u/yekai/caishen/money",number+"\n");
	write_file("/u/yekai/caishen/money",r_long+"\n");
	//write_file("/u/yekai/caishen/money",room_s);
        //message_job(HIG"天降财神，有宝落民间了！似乎在：\n"NOR+ r_long);
		message( "chat", HIG"天降财神，有宝落民间了！似乎在：\n"NOR+ r_long, users() );
}

int del_log(string x)
{
	string news="",olds,*line;
	int i,Bool=0,k;

	if( !( olds=read_file("/u/yekai/caishen/money") ) ) return 0;
	line=explode(olds,"\n");
	news="";
	for(i=0;i<sizeof(line);i++) {
		if(x==line[i]) Bool=1;
		if( Bool==1
		 && strlen(line[i])<=2
		 && line[i]!=x
		 && ( k=to_int(line[i]) )<=20
		 && k>=1 ) Bool=0;
		if(Bool==1) continue;
		news+=(line[i]+"\n");
	}
	rm("/u/yekai/caishen/money");
	write_file("/u/yekai/caishen/money",news);
	return 1;
}

string show_msg()
{
	string olds,news="",*line;
	int i,k,x,Bool=0,f=0,y;
	if( !(x=get_number())) return 0;
	k=random(x)+1;

	olds=read_file("/u/yekai/caishen/money");
	line=explode(olds,"\n");

	for(i=0;i<sizeof(line);i++) {
		if( strlen(line[i])<=2
		&& (y=to_int(line[i]))<=20
		&& y>=1 ) f++;
		if(f==k && Bool==0) Bool=1;
		if(f>k && Bool==1) Bool=0;
		if(Bool==0) continue;
		if( strlen(line[i])<=2
		&& y<=20
		&& y>=1 ) continue;
		news+=(line[i]+"\n");
	}
	return news;
}



