//fit source bounding box to destination bounding box//

vector srcBBmin , srcBBmax;
vector destBBmin , destBBmax;
srcBBmin = getbbox_min(0) * chv("scaleMin");
srcBBmax = getbbox_max(0)* chv("scaleMax");;
destBBmin = getbbox_min(1);
destBBmax = getbbox_max(1);

v@P = fit(v@P,srcBBmin,srcBBmax,destBBmin,destBBmax);


/////////////////////////////////////////////////////


//align an object to the center of a given bbox with offset

vector center = getbbox_center(1);

v@P = set(@P + center - chv("offset"));


/////////////////////////////////////////////////////

//draw polyline to nearest point
int nearp = nearpoint(1, @P);
vector pos = point(1, "P", nearp);
int newp = addpoint(0, pos);
addprim(0, "polyline", @ptnum, newp);


/////////////////////////////////////////////////////

//procedural hair curl
float angle, rand;
vector dir;
vector4 q;
dir = @N;
angle = @curveu*ch('curl_amount');
q = quaternion(v@t*angle);
dir = qrotate(q, dir);
rand = 1+rand(@ptnum)*ch('rand_offset');
@P += dir*ch('curl_offset')*rand;

/////////////////////////////////////////////////////


//hair curves density slider
if (rand(@primnum) > ch('density') ) {
   removeprim(0,@primnum, 1);
}

/////////////////////////////////////////////////////

//sin function to generate single braid
@P.x = sin(radians(@ptnum*45+ch("move")))*ch("size");
@P.z = sin(radians(@ptnum*ch("i")+ch("moveB")))*ch("th");

/////////////////////////////////////////////////////


//blend three objects together
vector blended01 = point(1, "P", @ptnum) - v@P;
vector blended02 = point(2, "P", @ptnum) - v@P;
vector blended03 = point(3, "P", @ptnum) - v@P;
v@P += blended01 + blended02 + blended03;
