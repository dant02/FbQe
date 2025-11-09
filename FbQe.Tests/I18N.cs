namespace FbQe.Tests
{
    [TestClass]
    public sealed class I18N
    {
        [TestMethod]
        public void GetCurrentUtcTimestamp_IsUtc()
        {
            var dt = FbQe.I18N.GetCurrentUtcTimestamp();
            Assert.AreEqual(DateTimeKind.Utc, dt.Kind);
        }
    }
}