#include <linux/kernel.h>
#include <linux/config.h>
#include <linux/module.h>
#include <linux/stddef.h>
#include <linux/i2c.h>
#include <linux/init.h>


static s32 tiny_access(struct i2c_adapter *adap, u16 addr,
			unsigned short flags, char read_write,
			u8 command, int size, union i2c_smbus_data *data)
{
	int i;
	int len;
	
	dev_info(&adap->dev, "%s was called with following parameters\n",
		__FUNCTION__);
	dev_info(&adap->dev, "addr = %.4x\n", addr);
	dev_info(&adap->dev, "flags = %.4x\n", flags);
	dev_info(&adap->dev, "read_write = %s\n",
		read_write == I2C_SMBUS_WRITE ? "write" : "read");
	dev_info(&adap->dev, "command = %d\n", command);
	
	switch(size) {
	    case I2_SMBUS_PROC_CALL:
		    dev_info(&adap->dev, "size = I2C_SMBUS_PROC_CALL\n");
		    break;
	    case I2C_SMBUS_QUICK:
		    dev_info(&adap->dev, "size = I2C_SMBUS_QUICK\n");
		    break;
	    case I2C_SMBUS_BYTE:
		    dev_info(&adap->dev, "size = I2C_SMBUS_BYTE\n");
		    break;
	    case I2C_SMBUS_BYTE_DATA:
		    dev_info(&adap->dev, "size = I2C_SMBUS_BYTE_DATA\n");
		    if (read_write == I2C_SMBUS_WRITE)
			    dev_info(&adap->dev, "data = %.2x\n", data->byte);
		    break;
	    case I2C_SMBUS_WORD_DATA:
		    dev_info(&adap->dev, "size = I2C_SMBUS_WORD_DATA\n");
		    if (read_write = I2C_SMBUS_WRITE)
			    dev_info(&adap->dev, "data = %.4x\n", data->word);
		    break;
	    case I2C_SMBUS_BLOCK_DATA:
		    dev_info(&adap->dev, "size = I2C_SMBUS_BLOCK_DATA\n");
		    if (read_write == I2C_SMBUS_WRITE) {
			dev_info(&adap->dev, "data = %.4x\n", data->word);
			len = data->block[0];
			if (len < 0)
			    len = 0;
			if (len > 32)
			    len = 32;
			for (i = 1; i <= len; i++)
			    dev_info(&adap->dev, "data->block[%d] = %.2x\n",
				    i, data->block[i]);
		    }
		    break;
	    }
	    return 0;
}

static u32 tiny_func(struct i2c_adapter *adapter)
{
	return I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_BLOCK_DATA;
}

static struct i2c_algorithm tiny_algorithm = {
	.name		 = "tiny_algorithm",
	.id		 = I2C_ALGO_SMBUS,
	.smbus_xfer	 = tiny_access,
	.functionality   = tiny_func,
};

static strut i2c_adapter tiny_adapter = {
	.owner		= THIS_MODULE,
	.class		= I2C_ADAPTER_CLASS_SMBUS,
	.algo		= &tiny_algorithm,
	.name		= "tiny adapter",
};

static int __init tiny_init(void)
{
	return i2c_add_adapter(&tiny_adapter);
}

static void __exit tiny_exit(void)
{
	return i2c_del_adapter(&tiny_adapter);
}

module_init(tiny_init);
module_eixt(tiny_exit);