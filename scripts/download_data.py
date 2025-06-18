from alpaca.data.historical import StockHistoricalDataClient
from alpaca.data.requests import StockBarsRequest
from alpaca.data.timeframe import TimeFrame
from alpaca.data.enums import DataFeed  # correct import in v0.40.1
from dotenv import load_dotenv
from datetime import datetime, timedelta
import os

load_dotenv()
API_KEY = os.getenv("ALPACA_API_KEY")
API_SECRET = os.getenv("ALPACA_SECRET_KEY")

client = StockHistoricalDataClient(API_KEY, API_SECRET)

end = datetime.utcnow()
start = end - timedelta(days=5)

req = StockBarsRequest(
    symbol_or_symbols=["SPY"],
    start=start,
    end=end,
    timeframe=TimeFrame.Minute,
    feed=DataFeed.IEX  # specify free IEX feed here
)

bars = client.get_stock_bars(req).df
bars = bars[bars.index.get_level_values("symbol") == "SPY"]
bars.reset_index(inplace=True)
os.makedirs("data", exist_ok=True)
bars.to_csv("data/spy_minute.csv", index=False)

print(f"✅ Saved {len(bars)} rows to data/spy_minute.csv")
