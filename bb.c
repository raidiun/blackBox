#include <stdio.h>

typedef enum {
    GPOS_EMPTY,
    GPOS_OFF,
	GPOS_FULL,
	} bbGPOS;

struct beam{
	int x;
	int y;
	int dir;
	int end;//If 0, path continues, if -1 absorbed, if 1~32 deflected
	};

bbGPOS grid[8][8];
int io[32];

void getAhead(struct beam inputBeam,bbGPOS retArr[3]) {
	int dx[3],dy[3];
	switch(inputBeam.dir) {
		case(0): {
			dx[0]=-1;dx[1]=0;dx[2]=1;
			dy[0]=1;dy[1]=1;dy[2]=1;
			break;
			}
		case(1): {
			dx[0]=1;dx[1]=1;dx[2]=1;
			dy[0]=1;dy[1]=0;dy[2]=-1;
			break;
			}
		case(2): {
			dx[0]=1;dx[1]=0;dx[2]=-1;
			dy[0]=-1;dy[1]=-1;dy[2]=-1;
			break;
			}
		case(3): {
			dx[0]=-1;dx[1]=-1;dx[2]=-1;
			dy[0]=-1;dy[1]=0;dy[2]=1;
			break;
			}
		}
	int tx,ty;
	for(int idx=0;idx<3;idx++) {
		tx=inputBeam.x+dx[idx];
		ty=inputBeam.y+dy[idx];
		if((0<=tx && tx<8)&&(0<=ty && ty<8)) {
			retArr[idx]=grid[tx][ty];
			}
		else {
			retArr[idx]=GPOS_OFF;
			}
		}
	}

void initGrid() {
	for(int x;x<8;x++) {
		for(int y;y<8;y++) {
			grid[x][y]=GPOS_EMPTY;
			}
		}
	}

struct beam clacNext(struct beam inputBeam) {
	int dx[4]={0,1,0,-1};
	int dy[4]={1,0,1,0};
	int rev[4]={2,3,0,1};
	int left[4]={3,0,1,2};
	int right[4]={1,2,3,0};
	
	struct beam outBeam;
	
	bbGPOS ahead[3];
	getAhead(inputBeam,ahead);
	
	if(ahead[0]==GPOS_EMPTY && ahead[1]==GPOS_EMPTY && ahead[2]==GPOS_EMPTY) {
		outBeam.x = inputBeam.x + dx[inputBeam.dir];
		outBeam.y = inputBeam.y + dy[inputBeam.dir];
		outBeam.dir = inputBeam.dir;
		outBeam.end = 0;
		return(outBeam);
		}
	if(ahead[0]==GPOS_OFF && ahead[1]==GPOS_OFF && ahead[2]==GPOS_OFF) {
		outBeam.x = inputBeam.x;
		outBeam.y = inputBeam.y;
		outBeam.dir = inputBeam.dir;
		outBeam.end = lookupExit(inputBeam);
		return(outBeam);
		}
	if(ahead[1]==GPOS_FULL) {
		outBeam.end = -1;
		return(outBeam);
		}
	if(ahead[0]==GPOS_FULL && ahead[2]==GPOS_FULL) {
		outBeam.x = inputBeam.x;
		outBeam.y = inputBeam.y;
		outBeam.dir = rev[inputBeam.dir];
		outBeam.end = 0;
		return(outBeam);
		}
	if(ahead[0]==GPOS_FULL) {
		outBeam.x = inputBeam.x;
		outBeam.y = inputBeam.y;
		outBeam.dir = right[inputBeam.dir];
		outBeam.end = 0;
		return(outBeam);
		}
	if(ahead[2]==GPOS_FULL) {
		outBeam.x = inputBeam.x;
		outBeam.y = inputBeam.y;
		outBeam.dir = left[inputBeam.dir];
		outBeam.end = 0;
		return(outBeam);
		}
	}

int main() {
	
	}
