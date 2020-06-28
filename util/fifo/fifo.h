/*


*/

#ifndef FIFO_H__
#define FIFO_H__


#ifdef __cplusplus
 extern "C" {
#endif
	 

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif		

#define is_power_of_2(x)	((x) != 0 && (((x) & ((x) - 1)) == 0))
		

struct fifo{
	volatile unsigned int in;
	volatile unsigned int out;
	unsigned	 int mask;
	unsigned char *data;
}; 

unsigned int fifo_unused(struct fifo *fifo);
unsigned int fifo_in(struct fifo *fifo, unsigned char *buf, unsigned int len);
unsigned int fifo_out(struct fifo *fifo, unsigned char *buf, unsigned int len);
unsigned int fifo_len(struct fifo *fifo);
int fifo_init(struct fifo *fifo, unsigned char *buffer, unsigned int size);
	 
#ifdef __cplusplus
}
#endif

#endif //FIFO_H__

